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
  builder.AddDoubleProperty(
      "Position", [&] { return GetPosition().value(); },
      nullptr);  // setter is null, cannot set position directly
  builder.AddDoubleProperty(
      "Velocity", [&] { return GetVelocity().value(); }, nullptr);
  builder.AddDoubleProperty(
      "Voltage", [&] { return GetSimVoltage().value(); }, nullptr);
  builder.AddDoubleProperty(
      "Position Target", [&] { return GetPositionTarget().value(); }, nullptr);
  builder.AddDoubleProperty(
      "Velocity Target", [&] { return GetVelocityTarget().value(); }, nullptr);
  builder.AddDoubleProperty(
      "P Gain", [&] { return _pidController.GetP(); }, [&](double P) { _pidController.SetP(P); });
  builder.AddDoubleProperty(
      "I Gain", [&] { return _pidController.GetI(); }, [&](double I) { _pidController.SetI(I); });
  builder.AddDoubleProperty(
      "D Gain", [&] { return _pidController.GetD(); }, [&](double D) { _pidController.SetD(D); });
  builder.AddDoubleProperty(
      "F Gain", [&] { return _pidController.GetFF(); }, [&](double F) { _pidController.SetFF(F); });
}

template <class Position>
void ICSparkMax<Position>::SetPositionTarget(Position_t target, units::volt_t arbFeedForward) {
  _positionTarget = target;
  _velocityTarget = Velocity_t{0};
  _voltageTarget = 0_V;
  _arbFeedForward = arbFeedForward;
  SetInternalControlType(Mode::kPosition);

  _pidController.SetReference(target.value(), GetControlType(), 0, _arbFeedForward.value());
  SyncSimPID();
}


template <class Position>
void ICSparkMax<Position>::SetSmartMotionTarget(Position_t target, units::volt_t arbFeedForward) {
  _positionTarget = target;
  _velocityTarget = Velocity_t{0};
  _voltageTarget = 0_V;
  _arbFeedForward = arbFeedForward;
  SetInternalControlType(Mode::kSmartMotion);

  _pidController.SetReference(target.value(), GetControlType(), 0, _arbFeedForward.value());
  SyncSimPID();
}

template <class Position>
void ICSparkMax<Position>::SetVelocityTarget(Velocity_t target, units::volt_t arbFeedForward) {
  _velocityTarget = target;
  _positionTarget = Position_t{0};
  _voltageTarget = 0_V;
  _arbFeedForward = arbFeedForward;
  SetInternalControlType(Mode::kVelocity);

  _pidController.SetReference(target.value(), GetControlType(), 0, _arbFeedForward.value());
  SyncSimPID();
}

template <class Position>
void ICSparkMax<Position>::Set(double speed) {
  _velocityTarget = Velocity_t{0};
  _positionTarget = Position_t{0};
  _voltageTarget = 0_V;
  SetInternalControlType(Mode::kDutyCycle);
  if (frc::RobotBase::IsSimulation()) {
    _pidController.SetReference(speed, Mode::kDutyCycle);
    SyncSimPID();
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
  SyncSimPID();
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
void ICSparkMax<Position>::SetPIDFF(double P, double I, double D, double FF) {
  _pidController.SetP(P);
  _pidController.SetI(I);
  _pidController.SetD(D);
  _pidController.SetFF(FF);
  SyncSimPID();
}

template <class Position>
void ICSparkMax<Position>::SetEncoderPosition(Position_t position) {
  _encoder->SetPosition(position.value());
}

template <class Position>
void ICSparkMax<Position>::SetClosedLoopOutputRange(double minOutputPercent,
                                                    double maxOutputPercent) {
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
                        _pidController.GetFF() * _velocityTarget.value()};
      break;

    case Mode::kPosition:
      output =
          units::volt_t{_simController.Calculate(GetPosition().value(), _positionTarget.value()) +
                        _pidController.GetFF() * _positionTarget.value()};
      break;

    case Mode::kVoltage:
      output = _voltageTarget;
      break;

    case Mode::kSmartMotion:
      output = units::volt_t{
          _simController.Calculate(GetVelocity().value(), GetCurrentSMVelocity().value()) +
          _pidController.GetFF() * GetCurrentSMVelocity().value()};
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
  return std::clamp(output, _pidController.GetOutputMin() * 12_V,
                    _pidController.GetOutputMax() * 12_V);
}

template <class Position>
void ICSparkMax<Position>::UpdateSimEncoder(Position_t position, Velocity_t velocity) {
  _encoder->SetPosition(position.value());
  _simVelocity = velocity;
}

template <class Position>
void ICSparkMax<Position>::SyncSimPID() {
  if (frc::RobotBase::IsReal()) {
    return;
  }

  _simController.SetP(_pidController.GetP());
  _simController.SetI(_pidController.GetI());
  _simController.SetD(_pidController.GetD());
  _simController.SetIntegratorRange(-_pidController.GetIMaxAccum(), _pidController.GetIMaxAccum());

  if (_controlType == Mode::kSmartMotion) {
    GenerateSMProfile();
  } else {
    _smartMotionProfileTimer.Stop();
  }
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

  return _simSmartMotionProfile.Calculate(_smartMotionProfileTimer.Get()).velocity;
}