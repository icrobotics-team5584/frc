#include "subsystems/SubClimber.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/RobotController.h>
#include <frc/simulation/RoboRioSim.h>
#include <frc/simulation/BatterySim.h>

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

  frc::SmartDashboard::PutData("Left Elevator Sim", &_leftMech);
  frc::SmartDashboard::PutData("Right Elevator Sim", &_rightMech);
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
  double lefterror = abs(_targetPosition - _encLeftElevator.GetPosition() );
  double righterror = abs(_targetPosition - _encRightElevator.GetPosition() );
  return (lefterror < kAllErr) &&(righterror < kAllErr);
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
    _targetPosition = 0;
    _pidLeftMotorController.SetReference(_targetPosition, rev::CANSparkMax::ControlType::kSmartMotion);
    _spmLeftElevator.Set(0);
  } else {
    frc::SmartDashboard::PutBoolean("Climber Left Safety", false);
  }
  if ((AtRightLimit() && GoingDown())) {
    _targetPosition = 0;
    _pidRightMotorController.SetReference(_targetPosition, rev::CANSparkMax::ControlType::kSmartMotion);
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

void SubClimber::Stow() {
  frc::SmartDashboard::PutBoolean("stow running", true); 
  _solTilter.Set(frc::DoubleSolenoid::kReverse);
  frc::SmartDashboard::PutBoolean("stow ran", true); 
}

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

void SubClimber::SimulationPeriodic() {
  // In this method, we update our simulation of what our elevator is doing
  // First, we set our "inputs" (voltages)
  if (_inSmartMotionMode) {
    if (GoingDown()) {
      _leftElevatorSim.SetInputVoltage(-12_V);
      _rightElevatorSim.SetInputVoltage(-12_V);
    } else {
      _leftElevatorSim.SetInputVoltage(12_V);
      _rightElevatorSim.SetInputVoltage(12_V);
    }
  } else {
    _leftElevatorSim.SetInputVoltage(
        units::volt_t(_spmLeftElevator.Get() * 12));
    _rightElevatorSim.SetInputVoltage(
        units::volt_t(_spmRightElevator.Get() * 12));
  }

  // Next, we update it. The standard loop time is 20ms.
  _leftElevatorSim.Update(20_ms);
  _rightElevatorSim.Update(20_ms);

  // Update the simulated limit switches based on the simulated elevators
  _leftLimitSim.SetValue(_leftElevatorSim.GetPosition() > 0_m);
  _rightLimitSim.SetValue(_leftElevatorSim.GetPosition() > 0_m);

  _encLeftElevator.SetPosition(_leftElevatorSim.GetPosition() /
                               kMaxElevatorHeight * MAX_POSITION);
  _encRightElevator.SetPosition(_leftElevatorSim.GetPosition() /
                                kMaxElevatorHeight * MAX_POSITION);

  // Update the displays based on the simulated elevators
  _leftLigament->SetLength(_leftElevatorSim.GetPosition().value());
  _rightLigament->SetLength(_rightElevatorSim.GetPosition().value());

  bool rotated = _solTilter.Get() == frc::DoubleSolenoid::Value::kForward;
  _leftLigament->SetAngle(rotated ? 100_deg : 90_deg);
  _rightLigament->SetAngle(rotated ? 100_deg : 90_deg);
}