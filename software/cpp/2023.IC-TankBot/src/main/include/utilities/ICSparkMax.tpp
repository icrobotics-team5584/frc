#include "utilities/ICSparkMax.h"

#include <frc/RobotBase.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <units/voltage.h>
#include <cstdlib>
#include <iostream>

template <class Position>
ICSparkMax<Position>::ICSparkMax(int deviceID, units::ampere_t currentLimit)
    : rev::CANSparkMax(deviceID, rev::CANSparkMaxLowLevel::MotorType::kBrushless) {
  RestoreFactoryDefaults();
  SetSmartCurrentLimit(currentLimit.value());
  SetConversionFactor(1); // Makes the internal encoder use revs per sec not revs per min

  _pidController.SetSmartMotionMinOutputVelocity(0);
  SetClosedLoopOutputRange(-1, 1);
}

template <class Position>
void ICSparkMax<Position>::InitSendable(wpi::SendableBuilder& builder) {
  builder.AddDoubleProperty("Position", [&] { return GetPosition().value(); }, nullptr);  // setter is null, cannot set position directly
  builder.AddDoubleProperty("Velocity", [&] { return GetVelocity().value(); }, nullptr);

  builder.AddDoubleProperty(
      "Voltage", [&] { 
        if (frc::RobotBase::IsSimulation()){return GetSimVoltage().value();}
        else {return CANSparkMax::GetAppliedOutput() * 12;}
      }, nullptr);

  // builder.AddDoubleProperty("Voltage", [&]{return GetSimVoltage().value();});

  builder.AddDoubleProperty(
      "Position Target", [&] { return GetPositionTarget().value(); }, nullptr);
  builder.AddDoubleProperty(
      "Velocity Target", [&] { return GetVelocityTarget().value(); }, nullptr);
  builder.AddDoubleProperty(
      "P Gain", [&] { return _simController.GetP(); }, [&](double P) { _simController.SetP(P); SyncSimPID();});
  builder.AddDoubleProperty(
      "I Gain", [&] { return _simController.GetI(); }, [&](double I) { _simController.SetI(I); SyncSimPID();});
  builder.AddDoubleProperty(
      "D Gain", [&] { return _simController.GetD(); }, [&](double D) { _simController.SetD(D); SyncSimPID();});
  builder.AddDoubleProperty(
      "F Gain", [&] { return _FF; }, [&](double F) { _FF = F; SyncSimPID();});
}

template <class Position>
void ICSparkMax<Position>::SetPosition(Position_t position){
  _encoder->SetPosition(position.value());
}

template <class Position>
void ICSparkMax<Position>::SetPositionTarget(Position_t target, units::volt_t arbFeedForward) {
  _positionTarget = target;
  _velocityTarget = Velocity_t{0};
  _voltageTarget = 0_V;
  _arbFeedForward = arbFeedForward;
  SetInternalControlType(Mode::kPosition);

  _pidController.SetReference(target.value(), GetControlType(), 0, _arbFeedForward.value());
}

template <class Position>
void ICSparkMax<Position>::SetSmartMotionTarget(Position_t target, units::volt_t arbFeedForward) {
  _positionTarget = target;
  _smartMotionProfileTimer.Start();
  _velocityTarget = Velocity_t{0};
  _voltageTarget = 0_V;
  _arbFeedForward = arbFeedForward;
  SetInternalControlType(Mode::kSmartMotion);

  _pidController.SetReference(target.value(), GetControlType(), 0, _arbFeedForward.value());
}

template <class Position>
void ICSparkMax<Position>::SetVelocityTarget(Velocity_t target, units::volt_t arbFeedForward) {
  _velocityTarget = target;
  _positionTarget = Position_t{0};
  _voltageTarget = 0_V;
  _arbFeedForward = arbFeedForward;
  SetInternalControlType(Mode::kVelocity);

  _pidController.SetReference(target.value(), GetControlType(), 0, _arbFeedForward.value());
}

template <class Position>
void ICSparkMax<Position>::Set(double speed) {
  _velocityTarget = Velocity_t{0};
  _positionTarget = Position_t{0};
  _voltageTarget = 0_V;
  SetInternalControlType(Mode::kDutyCycle);
  if (frc::RobotBase::IsSimulation()) {
    _pidController.SetReference(speed, Mode::kDutyCycle);
  }
  CANSparkMax::Set(speed);
}

template <class Position>
void ICSparkMax<Position>::SetVoltage(units::volt_t output) {
  _velocityTarget = Velocity_t{0};
  _positionTarget = Position_t{0};
  _voltageTarget = output;
  _arbFeedForward = 0_V;
  SetInternalControlType(Mode::kVoltage);

  _pidController.SetReference(output.value(), GetControlType(), 0, _arbFeedForward.value());
}

template <class Position>
void ICSparkMax<Position>::StopMotor() {
  _velocityTarget = Velocity_t{0};
  _positionTarget = Position_t{0};
  _voltageTarget = 0_V;
  SetInternalControlType(Mode::kDutyCycle);
  CANSparkMax::StopMotor();
}

template <class Position>
void ICSparkMax<Position>::SetInternalControlType(Mode controlType) {
  _controlType = controlType;
  _simControlMode.Set((int)_controlType);
}

template <class Position>
void ICSparkMax<Position>::ConfigSmartMotion(Velocity_t maxVelocity, Acceleration_t maxAcceleration,
                                             Position_t tolerance) {
  _pidController.SetSmartMotionMaxAccel(AccelToSparkRPMps(maxAcceleration));
  _pidController.SetSmartMotionMaxVelocity(VelToSparkRPM(maxVelocity));
  _pidController.SetSmartMotionAllowedClosedLoopError(tolerance.value());
}

template <class Position>
void ICSparkMax<Position>::SetConversionFactor(double rotationsToDesired) {
  _encoder->SetPositionConversionFactor(rotationsToDesired);
  // Need to divide vel by 60 because Spark Max uses Revs per minute not Revs per second
  _encoder->SetVelocityConversionFactor(rotationsToDesired / 60);
}

template <class Position>
void ICSparkMax<Position>::UseAlternateEncoder(int countsPerRev) {
  const double posConversion = _encoder->GetPositionConversionFactor();

  _encoder = std::make_unique<rev::SparkMaxAlternateEncoder>(
      CANSparkMax::GetAlternateEncoder(countsPerRev));
  _pidController.SetFeedbackDevice(*_encoder);

  SetConversionFactor(posConversion);
}

template <class Position>
void ICSparkMax<Position>::UseAbsoluteEncoder(rev::SparkMaxAbsoluteEncoder& encoder) {
  _pidController.SetFeedbackDevice(encoder);
}

template <class Position>
void ICSparkMax<Position>::EnableSensorWrapping(double min, double max) {
  _pidController.SetPositionPIDWrappingMaxInput(max);
  _pidController.SetPositionPIDWrappingMinInput(min);
  _pidController.SetPositionPIDWrappingEnabled(true);
}

template <class Position>
void ICSparkMax<Position>::SetPIDFF(double P, double I, double D, double FF) {
  _simController.SetP(P);
  _simController.SetI(I);
  _simController.SetD(D);
  _FF = FF;
  SyncSimPID();

}

template <class Position>
void ICSparkMax<Position>::SetEncoderPosition(Position_t position) {
  _encoder->SetPosition(position.value());
}

template <class Position>
void ICSparkMax<Position>::SetClosedLoopOutputRange(double minOutputPercent,
                                                    double maxOutputPercent) {
  _minPidOutput = minOutputPercent;
  _maxPidOutput = maxOutputPercent;                                                    
  _pidController.SetOutputRange(minOutputPercent, maxOutputPercent);
}

template <class Position>
ICSparkMax<Position>::Velocity_t ICSparkMax<Position>::GetVelocity() {
  if (frc::RobotBase::IsSimulation()) {
    return _simVelocity;
  } else {
    return Velocity_t{_encoder->GetVelocity()};
  }
}

template <class Position>
units::volt_t ICSparkMax<Position>::GetSimVoltage() {
  units::volt_t output = 0_V;

  switch (_controlType) {
    case Mode::kDutyCycle:
      output = units::volt_t{CANSparkMax::Get() * 12};
      break;

    case Mode::kVelocity:
      output =
          units::volt_t{_simController.Calculate(GetVelocity().value(), _velocityTarget.value()) +
                        _FF * _velocityTarget.value()};
      break;

    case Mode::kPosition:
      output =
          units::volt_t{_simController.Calculate(GetPosition().value(), _positionTarget.value()) +
                        _FF * _positionTarget.value()};
      break;

    case Mode::kVoltage:
      output = _voltageTarget;
      break;

    case Mode::kSmartMotion:
      output = units::volt_t{
          _simController.Calculate(GetVelocity().value(), GetCurrentSMVelocity().value()) +
          _FF * GetCurrentSMVelocity().value()};
      break;

    case Mode::kCurrent:
      std::cout << "Warning: closed loop Current control not supported by ICSparkMax in "
                   "Simulation\n";
      break;

    case Mode::kSmartVelocity:
      std::cout << "Warning: smart velocity control not supported by ICSparkMax in Simulation\n";
      break;
  }
  output += _arbFeedForward;
  return std::clamp(output, _minPidOutput * 12_V, _maxPidOutput * 12_V);
}

template <class Position>
void ICSparkMax<Position>::UpdateSimEncoder(Position_t position, Velocity_t velocity) {
  _encoder->SetPosition(position.value());
  _simVelocity = velocity;
}

template <class Position>
void ICSparkMax<Position>::SyncSimPID() {
  double conversion = (GetControlType() == Mode::kPosition)
    ? _encoder->GetPositionConversionFactor()
    : _encoder->GetVelocityConversionFactor();

  _pidController.SetP(_simController.GetP() * conversion);
  _pidController.SetI(_simController.GetI() * conversion);
  _pidController.SetD(_simController.GetD() * conversion);
  _pidController.SetFF(_FF * conversion);
  _simController.SetIntegratorRange(-_pidController.GetIMaxAccum(), _pidController.GetIMaxAccum());
}

template <class Position>
void ICSparkMax<Position>::GenerateSMProfile() {
  _smartMotionProfileTimer.Reset();
  _smartMotionProfileTimer.Start();

  Velocity_t maxVel = SparkRPMToVel(_pidController.GetSmartMotionMaxVelocity());
  Acceleration_t maxAccel = SparkRPMpsToAccel(_pidController.GetSmartMotionMaxAccel());
  _simSmartMotionProfile = frc::TrapezoidProfile<Position>{
      {maxVel, maxAccel},                // constraints
      {_positionTarget, Velocity_t{0}},  // goal state
      {GetPosition(), GetVelocity()}     // current state
  };
}

template <class Position>
ICSparkMax<Position>::Velocity_t ICSparkMax<Position>::GetCurrentSMVelocity() {
  if (frc::RobotBase::IsReal() || _controlType != Mode::kSmartMotion) {
    return Velocity_t{0};
  }

  if (_smartMotionProfileTimer.Get() > 0.2_s) {
    GenerateSMProfile();
  }

  Position_t error = units::math::abs(_positionTarget - GetPosition());
  Position_t tolerance = SparkRevsToPos(_pidController.GetSmartMotionAllowedClosedLoopError());
  if (error < tolerance) {
    return Velocity_t{0};
  }

auto velocity = _simSmartMotionProfile.Calculate(_smartMotionProfileTimer.Get()).velocity;
  return velocity;
}