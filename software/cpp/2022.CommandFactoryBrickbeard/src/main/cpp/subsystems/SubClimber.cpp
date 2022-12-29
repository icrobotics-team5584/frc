#include "subsystems/SubClimber.h"
#include <frc/smartdashboard/SmartDashboard.h>

SubClimber::SubClimber() {
  frc::SmartDashboard::PutData("climber/left motor", (wpi::Sendable*)&_leftMotor);
  frc::SmartDashboard::PutData("climber/right motor", (wpi::Sendable*)&_rightMotor);

  _leftMotor.SetConversionFactor(POS_CONVERSION);
  _leftMotor.ConfigSmartMotion(MAX_VEL, MAX_ACCEL, TOLERANCE);
  _leftMotor.SetPIDFF(P, I, D, F);
  _rightMotor.SetConversionFactor(POS_CONVERSION);
  _rightMotor.ConfigSmartMotion(MAX_VEL, MAX_ACCEL, TOLERANCE);
  _rightMotor.SetPIDFF(P, I, D, F);
};

void SubClimber::Periodic() {
  StopMotorsFromHittingEnds();
}

void SubClimber::DriveTo(units::meter_t height) {
  height = std::clamp(height, MIN_HEIGHT, MAX_HEIGHT);
  _leftMotor.SetSmartMotionTarget(height);
  _rightMotor.SetSmartMotionTarget(height);
}

void SubClimber::ManualDrive(double speed) {
  double leftSpeed = speed;
  double rightSpeed = speed;
  if (AtLowerLeftLimit() && leftSpeed < 0) {
    leftSpeed = 0;
  }
  if (AtLowerRightLimit() && rightSpeed < 0) {
    rightSpeed = 0;
  }
  _leftMotor.Set(leftSpeed);
  _rightMotor.Set(rightSpeed);
}

void SubClimber::Rotate() {
  _tilterPiston.Set(frc::DoubleSolenoid::kForward);
}

void SubClimber::Stow() {
  _tilterPiston.Set(frc::DoubleSolenoid::kReverse);
}

bool SubClimber::GoingDown() {
  return _leftMotor.GetVelocity() < 0_mps || _rightMotor.GetVelocity() < 0_mps;
}

bool SubClimber::GoingUp() {
  return _leftMotor.GetVelocity() > 0_mps || _rightMotor.GetVelocity() > 0_mps;
}

bool SubClimber::IsAtTargetPosition() {
  return units::math::abs(_leftMotor.GetPosError()) < TOLERANCE &&
         units::math::abs(_rightMotor.GetPosError()) < TOLERANCE;
}

void SubClimber::StopMotorsFromHittingEnds() {
  if (AtLowerLeftLimit() && GoingDown()) {
    _leftMotor.StopMotor();
  }
  if (AtLowerRightLimit() && GoingDown()) {
    _rightMotor.StopMotor();
  }
  if (AtUpperLeftLimit() && GoingUp()) {
    _leftMotor.StopMotor();
  }
  if (AtUpperRightLimit() && GoingUp()) {
    _rightMotor.StopMotor();
  }
}

void SubClimber::SimulationPeriodic() {
  _leftElevatorSim.SetInputVoltage(_leftMotor.GetSimVoltage());
  _rightElevatorSim.SetInputVoltage(_rightMotor.GetSimVoltage());

  _leftElevatorSim.Update(20_ms);
  _rightElevatorSim.Update(20_ms);

  _lowerLeftLimitSim.SetValue(_leftElevatorSim.GetPosition() <= 0_m);
  _lowerRightLimitSim.SetValue(_rightElevatorSim.GetPosition() <= 0_m);
  _upperLeftLimitSim.SetValue(_leftElevatorSim.GetPosition() >= MAX_HEIGHT);
  _upperRightLimitSim.SetValue(_rightElevatorSim.GetPosition() >= MAX_HEIGHT);

  auto leftPos = _leftElevatorSim.GetPosition();
  auto rightPos = _rightElevatorSim.GetPosition();
  auto leftVel = _leftElevatorSim.GetVelocity();
  auto rightVel = _rightElevatorSim.GetVelocity();
  _leftMotor.UpdateSimEncoder(leftPos, leftVel);
  _rightMotor.UpdateSimEncoder(rightPos, rightVel);
}