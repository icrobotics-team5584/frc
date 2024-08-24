#include "utilities/ICSparkBase.h"

#include <frc/RobotBase.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <units/voltage.h>
#include <wpi/MathExtras.h>
#include <cstdlib>
#include <iostream>

ICSpark::ICSpark(rev::CANSparkBase* spark,
                         rev::SparkRelativeEncoder&& inbuiltEncoder,
                         units::ampere_t currentLimit)
    : _spark(spark), _encoder{std::move(inbuiltEncoder)} {
  _spark->RestoreFactoryDefaults();
  _spark->SetSmartCurrentLimit(currentLimit.value());
  SetConversionFactor(1);  // Makes the internal encoder use revs per sec not revs per min

  _pidController.SetSmartMotionMinOutputVelocity(0);
  SetClosedLoopOutputRange(-1, 1);
}

void ICSpark::InitSendable(wpi::SendableBuilder& builder) {
  // clang-format off
  builder.AddDoubleProperty("Position", [&] { return GetPosition().value(); }, nullptr);  // setter is null, cannot set position directly
  builder.AddDoubleProperty("Velocity", [&] { return GetVelocity().value(); }, nullptr);
  builder.AddDoubleProperty("Position Target", [&] { return _positionTarget.value(); }, [&](double targ) { SetPositionTarget(targ*1_tr); });
  builder.AddDoubleProperty("Velocity Target", [&] { return _velocityTarget.value(); }, [&](double targ) { SetVelocityTarget(targ*1_tps); });
  builder.AddDoubleProperty("Motion Profile Position Target", [&] { return _latestMotionTarget.position.value(); }, [&](double targ) { SetMotionProfileTarget(targ*1_tr); });
  builder.AddDoubleProperty("Motion Profile Velocity Target", [&] { return _latestMotionTarget.velocity.value(); }, nullptr);

  builder.AddDoubleProperty("Voltage", [&] { 
        return (frc::RobotBase::IsSimulation()) 
          ? GetSimVoltage().value() 
          : _spark->GetAppliedOutput() * _spark->GetBusVoltage();
      }, nullptr);

  builder.AddDoubleProperty("Gains/FB P Gain", [&] { return _simController.GetP(); }, [&](double P) { SetFeedbackProportional(P); });
  builder.AddDoubleProperty("Gains/FB I Gain", [&] { return _simController.GetI(); }, [&](double I) { SetFeedbackIntegral(I); });
  builder.AddDoubleProperty("Gains/FB D Gain", [&] { return _simController.GetD(); }, [&](double D) { SetFeedbackDerivative(D); });
  builder.AddDoubleProperty("Gains/FF S Gain", [&] { return _feedforwardStaticFriction.value(); }, [&](double S) { SetFeedforwardStaticFriction(S*1_V); });
  builder.AddDoubleProperty("Gains/FF V Gain", [&] { return _feedforwardVelocity.value(); },       [&](double V) { SetFeedforwardVelocity(VoltsPerTps{V}); });
  builder.AddDoubleProperty("Gains/FF A Gain", [&] { return _feedforwardAcceleration.value(); },   [&](double A) { SetFeedforwardAcceleration(VoltsPerTpsSq{A}); });
  builder.AddDoubleProperty("Gains/FF Linear G Gain",    [&] { return _feedforwardLinearGravity.value(); },    [&](double lG) { SetFeedforwardLinearGravity(lG*1_V); });
  builder.AddDoubleProperty("Gains/FF Rotational G Gain",[&] { return _feedforwardRotationalGravity.value(); },[&](double rG) { SetFeedforwardRotationalGravity(rG*1_V); });
  // clang-format on
}

void ICSpark::SetPosition(units::turn_t position) {
  _encoder.SetPosition(position.value());
}

void ICSpark::SetPositionTarget(units::turn_t target, units::volt_t arbFeedForward) {
  _positionTarget = target;
  _velocityTarget = units::turns_per_second_t{0};
  _voltageTarget = 0_V;
  _arbFeedForward = arbFeedForward;
  SetInternalControlType(ControlType::kPosition);

  _pidController.SetReference(target.value(),
                              rev::CANSparkLowLevel::ControlType::kPosition, 0,
                              _arbFeedForward.value());
}

void ICSpark::SetSmartMotionTarget(units::turn_t target, units::volt_t arbFeedForward) {
  _positionTarget = target;
  _velocityTarget = units::turns_per_second_t{0};
  _voltageTarget = 0_V;
  _arbFeedForward = arbFeedForward;
  _latestMotionTarget = {GetPosition(), GetVelocity()};
  SetInternalControlType(ControlType::kSmartMotion);

  _pidController.SetReference(target.value(),
                              rev::CANSparkLowLevel::ControlType::kSmartMotion,
                              0, _arbFeedForward.value());
}

void ICSpark::SetMotionProfileTarget(units::turn_t target, units::volt_t arbFeedForward) {
  _positionTarget = target;
  _velocityTarget = units::turns_per_second_t{0};
  _voltageTarget = 0_V;
  _arbFeedForward = arbFeedForward;
  _latestMotionTarget = {GetPosition(), GetVelocity()};
  SetInternalControlType(ControlType::kMotionProfile);

  _pidController.SetReference(_latestMotionTarget.position.value(),
                              rev::CANSparkLowLevel::ControlType::kPosition, 0,
                              _arbFeedForward.value());
}

void ICSpark::SetVelocityTarget(units::turns_per_second_t target, units::volt_t arbFeedForward) {
  _velocityTarget = target;
  _positionTarget = units::turn_t{0};
  _voltageTarget = 0_V;
  _arbFeedForward = arbFeedForward;
  SetInternalControlType(ControlType::kVelocity);

  _pidController.SetReference(target.value(),
                              rev::CANSparkLowLevel::ControlType::kVelocity, 0,
                              _arbFeedForward.value());
}

void ICSpark::SetDutyCycle(double speed) {
  _velocityTarget = units::turns_per_second_t{0};
  _positionTarget = units::turn_t{0};
  _voltageTarget = 0_V;
  SetInternalControlType(ControlType::kDutyCycle);
  _spark->Set(speed);
}

void ICSpark::SetVoltage(units::volt_t output) {
  _velocityTarget = units::turns_per_second_t{0};
  _positionTarget = units::turn_t{0};
  _voltageTarget = output;
  _arbFeedForward = 0_V;
  SetInternalControlType(ControlType::kVoltage);

  _pidController.SetReference(output.value(),
                              rev::CANSparkLowLevel::ControlType::kVoltage, 0,
                              _arbFeedForward.value());
}

void ICSpark::UpdateControls(units::second_t loopTime) {
  switch (GetControlType()) {
    case ControlType::kMotionProfile: {
      auto prevVelTarget = _latestMotionTarget.velocity;
      _latestMotionTarget = CalcNextMotionTarget(loopTime);
      auto accelTarget =
          (_latestMotionTarget.velocity - prevVelTarget) / loopTime;
      _arbFeedForward = CalculateFeedforward(accelTarget);
      _pidController.SetReference(_latestMotionTarget.position.value(),
                                  rev::CANSparkLowLevel::ControlType::kPosition,
                                  0, _arbFeedForward.value());
      break;
    }
    case ControlType::kSmartMotion:
      SetSmartMotionTarget(_positionTarget, CalculateFeedforward());
      break;
    case ControlType::kPosition:
      SetPositionTarget(_positionTarget, CalculateFeedforward());
      break;
    case ControlType::kVelocity:
      SetVelocityTarget(_velocityTarget, CalculateFeedforward());
      break;
    default:
      break;
  }
}

units::volt_t ICSpark::CalculateFeedforward(
    units::turns_per_second_squared_t accelerationTarget) {
  auto velTarget = _latestMotionTarget.velocity;
  auto posTarget = _latestMotionTarget.position;
  return _feedforwardStaticFriction * wpi::sgn(velTarget) +
         _feedforwardLinearGravity +
         _feedforwardRotationalGravity * units::math::cos(posTarget) +
         _feedforwardVelocity * velTarget +
         _feedforwardAcceleration * accelerationTarget;
}

void ICSpark::Stop() {
  _velocityTarget = units::turns_per_second_t{0};
  _positionTarget = units::turn_t{0};
  _voltageTarget = 0_V;
  SetInternalControlType(ControlType::kDutyCycle);
  _spark->StopMotor();
}

void ICSpark::SetInternalControlType(ControlType controlType) {
  _controlType = controlType;
}

rev::CANSparkLowLevel::ControlType ICSpark::GetREVControlType() {
  auto controlType = GetControlType();
  if (controlType == ControlType::kMotionProfile) {
    return rev::CANSparkLowLevel::ControlType::kPosition;
  } else {
    return (rev::CANSparkLowLevel::ControlType)controlType;
  }
}

void ICSpark::ConfigMotion(units::turns_per_second_t maxVelocity,
                                   units::turns_per_second_squared_t maxAcceleration,
                                   units::turn_t tolerance) {
  _pidController.SetSmartMotionMaxAccel(maxAcceleration.value());
  _pidController.SetSmartMotionMaxVelocity(maxVelocity.value());
  _pidController.SetSmartMotionAllowedClosedLoopError(tolerance.value());

  _motionProfile = frc::TrapezoidProfile<units::turns>{{maxVelocity, maxAcceleration}};
}

void ICSpark::SetConversionFactor(double rotationsToDesired) {
  _encoder.SetConversionFactor(rotationsToDesired);
}

void ICSpark::UseAbsoluteEncoder(units::turn_t zeroOffset) {
  auto absEncoder = _spark->GetAbsoluteEncoder(rev::SparkAbsoluteEncoder::Type::kDutyCycle);
  absEncoder.SetAverageDepth(128); 
  _spark->SetPeriodicFramePeriod(rev::CANSparkLowLevel::PeriodicFrame::kStatus5, 10);
  _spark->SetPeriodicFramePeriod(rev::CANSparkLowLevel::PeriodicFrame::kStatus6, 10);
  absEncoder.SetZeroOffset(zeroOffset.value());
  _encoder.UseAbsolute(std::move(absEncoder));
  _pidController.SetFeedbackDevice(_encoder.GetPIDFeedbackDevice());
}

void ICSpark::EnableClosedLoopWrapping(units::turn_t min, units::turn_t max) {
  _pidController.SetPositionPIDWrappingMinInput(min.value());
  _pidController.SetPositionPIDWrappingMaxInput(max.value());
  _pidController.SetPositionPIDWrappingEnabled(true);
  _simController.EnableContinuousInput(min.value(), max.value());
}

void ICSpark::SetFeedbackGains(double P, double I, double D) {
  SetFeedbackProportional(P);
  SetFeedbackIntegral(I);
  SetFeedbackDerivative(D);
}

void ICSpark::SetFeedbackProportional(double P) {
  _pidController.SetP(P);
  _simController.SetP(P);
}

void ICSpark::SetFeedbackIntegral(double I) {
  _pidController.SetI(I);
  _simController.SetI(I);
}

void ICSpark::SetFeedbackDerivative(double D) {
  _pidController.SetD(D);
  _simController.SetD(D);
}

void ICSpark::SetFeedforwardGains(units::volt_t S, units::volt_t G,
                                  bool gravityIsRotational, VoltsPerTps V,
                                  VoltsPerTpsSq A) {
  SetFeedforwardStaticFriction(S);
  SetFeedforwardVelocity(V);
  SetFeedforwardAcceleration(A);
  if (gravityIsRotational) {
    SetFeedforwardRotationalGravity(G);
  } else {
    SetFeedforwardLinearGravity(G);
  }
}

void ICSpark::SetFeedforwardStaticFriction(units::volt_t S) {
  _feedforwardStaticFriction = S;
}

void ICSpark::SetFeedforwardLinearGravity(units::volt_t linearG) {
  _feedforwardLinearGravity = linearG;
}

void ICSpark::SetFeedforwardRotationalGravity(units::volt_t rotationalG) {
  _feedforwardRotationalGravity = rotationalG;
}

void ICSpark::SetFeedforwardVelocity(VoltsPerTps V) {
  _feedforwardVelocity = V;
}

void ICSpark::SetFeedforwardAcceleration(VoltsPerTpsSq A) {
  _feedforwardAcceleration = A;
}

void ICSpark::SetClosedLoopOutputRange(double minOutputPercent, double maxOutputPercent) {
  _minPidOutput = minOutputPercent;
  _maxPidOutput = maxOutputPercent;
  _pidController.SetOutputRange(minOutputPercent, maxOutputPercent);
}

units::turns_per_second_t ICSpark::GetVelocity() {
  if (frc::RobotBase::IsSimulation()) {
    return _simVelocity;
  } else {
    return units::turns_per_second_t{_encoder.GetVelocity()};
  }
}

units::volt_t ICSpark::GetSimVoltage() {
  units::volt_t output = 0_V;

  switch (_controlType) {
    case ControlType::kDutyCycle:
      output = units::volt_t{_spark->Get() * 12};
      break;

    case ControlType::kVelocity:
      // Spark internal PID uses native units (motor shaft RPM)
      // so divide by conversion factor to use that
      output = units::volt_t{_simController.Calculate(GetVelocity().value(),
                                                      _velocityTarget.value()) /
                                 _encoder.GetVelocityConversionFactor()};
      break;

    case ControlType::kPosition:
      // Spark internal PID uses native units (motor shaft rotations)
      // so divide by conversion factor to use that
      output = units::volt_t{_simController.Calculate(GetPosition().value(),
                                                      _positionTarget.value()) /
                                 _encoder.GetPositionConversionFactor()};
      break;

    case ControlType::kVoltage:
      output = _voltageTarget;
      break;

    case ControlType::kSmartMotion:
      output = units::volt_t{
          _simController.Calculate(GetVelocity().value(),
                                   _latestMotionTarget.velocity.value()) /
          _encoder.GetVelocityConversionFactor()};
      break;

    case ControlType::kMotionProfile:
      output = units::volt_t{
          _simController.Calculate(GetPosition().value(),
                                   _latestMotionTarget.position.value()) /
          _encoder.GetPositionConversionFactor()};
      break;

    case ControlType::kCurrent:
      break;
  }
  output += _arbFeedForward;
  return std::clamp(output, _minPidOutput * 12_V, _maxPidOutput * 12_V);
}

void ICSpark::UpdateSimEncoder(units::turn_t position, units::turns_per_second_t velocity) {
  _encoder.SetPosition(position.value());
  _simVelocity = velocity;
}

bool ICSpark::InMotionMode() {
  return GetControlType() == ControlType::kMotionProfile ||
         GetControlType() == ControlType::kSmartMotion;
}

ICSpark::MPState ICSpark::CalcNextMotionTarget(units::second_t lookahead) {
  units::turn_t error = units::math::abs(_positionTarget - GetPosition());
  units::turn_t tolerance = _pidController.GetSmartMotionAllowedClosedLoopError() * 1_tr;
  if (error < tolerance) {
    return MPState{GetPosition(), 0_tps};
  }

  return _motionProfile.Calculate(
      lookahead, _latestMotionTarget,
      {_positionTarget, units::turns_per_second_t{0}});
}
