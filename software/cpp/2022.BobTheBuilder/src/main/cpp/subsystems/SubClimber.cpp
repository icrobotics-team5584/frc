#include "subsystems/SubClimber.h"
#include "frc/smartdashboard/SmartDashboard.h"


SubClimber::SubClimber() {
  _spmLeftElevator.RestoreFactoryDefaults();
  _spmLeftElevator.SetSmartCurrentLimit(40);
  _spmLeftElevator.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  _spmRightElevator.RestoreFactoryDefaults();
  _spmRightElevator.SetSmartCurrentLimit(40);
  _spmRightElevator.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  
  _spmLeftElevator.SetInverted(true);

  _pidLeftMotorController.SetP(kP);
  _pidLeftMotorController.SetI(kI);
  _pidLeftMotorController.SetD(kD);
  _pidLeftMotorController.SetIZone(KIz);
  _pidLeftMotorController.SetFF(kFF);
  _pidLeftMotorController.SetOutputRange(kMinOutput, kMaxOutPut);
  _pidLeftMotorController.SetSmartMotionMaxVelocity(kFastMaxVel);
  _pidLeftMotorController.SetSmartMotionMinOutputVelocity(kMinVel);
  _pidLeftMotorController.SetSmartMotionMaxAccel(kMaxAcc);
  _pidLeftMotorController.SetSmartMotionAllowedClosedLoopError(kAllErr);
  _pidRightMotorController.SetP(kP);
  _pidRightMotorController.SetI(kI);
  _pidRightMotorController.SetD(kD);
  _pidRightMotorController.SetIZone(KIz);
  _pidRightMotorController.SetFF(kFF);
  _pidRightMotorController.SetOutputRange(kMinOutput, kMaxOutPut);
  _pidRightMotorController.SetSmartMotionMaxVelocity(kFastMaxVel);
  _pidRightMotorController.SetSmartMotionMinOutputVelocity(kMinVel);
  _pidRightMotorController.SetSmartMotionMaxAccel(kMaxAcc);
  _pidRightMotorController.SetSmartMotionAllowedClosedLoopError(kAllErr);

  SetEncoders(MIN_POSITION);  // Assume we turn the robot on with the arms down
}

void SubClimber::SetMaxSpeed(){
  _pidRightMotorController.SetSmartMotionMaxVelocity(kFastMaxVel);
  _pidLeftMotorController.SetSmartMotionMaxVelocity(kFastMaxVel);
}

void SubClimber::SetMinSpeed(){
  _pidRightMotorController.SetSmartMotionMaxVelocity(kSlowMaxVel);
  _pidLeftMotorController.SetSmartMotionMaxVelocity(kSlowMaxVel);
}

bool SubClimber::IsAtTargetPosition() {
  double error = abs(_targetPosition - _encLeftElevator.GetPosition() );
  return (error < kAllErr);
}
void SubClimber::SetEncoders(double value) {
  _encLeftElevator.SetPosition(value);
  _encRightElevator.SetPosition(value);
}

void SubClimber::Periodic() {
  // Dashboard Logging
  frc::SmartDashboard::PutNumber("Left Climber Position", _encLeftElevator.GetPosition());
  frc::SmartDashboard::PutNumber("Right Climber Position", _encRightElevator.GetPosition());
  frc::SmartDashboard::PutBoolean("Left climber limit", AtLeftLimit());
  frc::SmartDashboard::PutBoolean("Right climber limit", AtRightLimit());
  frc::SmartDashboard::PutBoolean("climber Going Down", GoingDown());
  frc::SmartDashboard::PutBoolean("climber in smart motion control", _inSmartMotionMode);
  frc::SmartDashboard::PutNumber("climber target position", _targetPosition);
  frc::SmartDashboard::PutNumber("climber left duty cycle", _spmLeftElevator.GetAppliedOutput());
  frc::SmartDashboard::PutNumber("climber right duty cycle", _spmRightElevator.GetAppliedOutput());

  // Reset encoders when limit switch is pressed
  if (AtLeftLimit()) {
    _encLeftElevator.SetPosition(MIN_POSITION);
  }
  if (AtRightLimit()) {
    _encRightElevator.SetPosition(MIN_POSITION);
  }

  // Don't let the climber kill itself
  if ((AtLeftLimit() && GoingDown())) {
    frc::SmartDashboard::PutBoolean("Climber Left Safety", true);
    _spmLeftElevator.Set(0);
  } else {
    frc::SmartDashboard::PutBoolean("Climber Left Safety", false);
  }
  if ((AtRightLimit() && GoingDown())) {
    _spmRightElevator.Set(0);
    frc::SmartDashboard::PutBoolean("Climber Right Safety", true);
  } else {
    frc::SmartDashboard::PutBoolean("Climber Right Safety", false);
  }
}

void SubClimber::ManualDrive(double speed) {
  _inSmartMotionMode = false;
  double leftSpeed = speed;
  double rightSpeed = speed;
  if (AtLeftLimit() && leftSpeed < 0) leftSpeed = 0;
  if (AtRightLimit() && rightSpeed < 0) rightSpeed = 0;
  _spmLeftElevator.Set(leftSpeed);
  _spmRightElevator.Set(rightSpeed);
}

void SubClimber::DriveTo(double position) {
  _targetPosition = position;
  _inSmartMotionMode = true;
  _pidLeftMotorController.SetReference(_targetPosition, rev::CANSparkMax::ControlType::kSmartMotion);
  _pidRightMotorController.SetReference(_targetPosition, rev::CANSparkMax::ControlType::kSmartMotion);
}

void SubClimber::Extend() { DriveTo(MAX_POSITION); }

void SubClimber::Retract() { DriveTo(MIN_POSITION + SAFETY_FACTOR); }

void SubClimber::Rotate() { _solTilter.Set(frc::DoubleSolenoid::kForward); }

void SubClimber::Stow() { _solTilter.Set(frc::DoubleSolenoid::kReverse); }

bool SubClimber::AtLeftLimit() { return !_lmtLeft.Get(); }

bool SubClimber::AtRightLimit() { return !_lmtRight.Get(); }

bool SubClimber::GoingDown() {
  if (_inSmartMotionMode) {
    return _encLeftElevator.GetPosition() > _targetPosition ||
           _encRightElevator.GetPosition() > _targetPosition;
  } else {
    return _spmRightElevator.Get() < 0 || _spmRightElevator.Get() < 0;
  }
  
}

