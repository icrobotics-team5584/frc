// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubClimber.h"
#include "frc/smartdashboard/SmartDashboard.h"

SubClimber::SubClimber(){
  double kP = 0.001, kI = 0, kD = 0, KIz = 0, kFF = 0, kMaxOutPut = 1, kMinOutput = -1;
  double kMaxVel = 2600, kMinVel = 0, kMaxAcc = 2600, kAllErr = 0;

  _spmLeftElevator.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  _spmRightElevator.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

  _pidLeftMotorController.SetP(-kP);
  _pidLeftMotorController.SetI(kI);
  _pidLeftMotorController.SetD(kD);
  _pidLeftMotorController.SetIZone(KIz);
  _pidLeftMotorController.SetFF(kFF);
  _pidLeftMotorController.SetOutputRange(kMinOutput, kMaxOutPut);

  _pidLeftMotorController.SetSmartMotionMaxVelocity(kMaxVel);
  _pidLeftMotorController.SetSmartMotionMinOutputVelocity(kMinVel);
  _pidLeftMotorController.SetSmartMotionMaxAccel(kMaxAcc);
  _pidLeftMotorController.SetSmartMotionAllowedClosedLoopError(kAllErr);

  _pidRightMotorController.SetP(kP);
  _pidRightMotorController.SetI(kI);
  _pidRightMotorController.SetD(kD);
  _pidRightMotorController.SetIZone(KIz);
  _pidRightMotorController.SetFF(kFF);
  _pidRightMotorController.SetOutputRange(kMinOutput, kMaxOutPut);

  _pidRightMotorController.SetSmartMotionMaxVelocity(kMaxVel);
  _pidRightMotorController.SetSmartMotionMinOutputVelocity(kMinVel);
  _pidRightMotorController.SetSmartMotionMaxAccel(kMaxAcc);
  _pidRightMotorController.SetSmartMotionAllowedClosedLoopError(kAllErr);
}

void SubClimber::ResetEncoder(){
  _encLeftElevator.SetPosition(0);
  _encRightElevator.SetPosition(0);
}

// This method will be called once per scheduler run
void SubClimber::Periodic() {
  frc::SmartDashboard::PutNumber("Left Climber Position", _encLeftElevator.GetPosition());
  frc::SmartDashboard::PutNumber("Right Climber Position", _encRightElevator.GetPosition());
  frc::SmartDashboard::PutNumber("Left Climber Speed", _spmLeftElevator.Get());
  frc::SmartDashboard::PutNumber("Right Climber Speed", _spmRightElevator.Get());
}

void SubClimber::Extend() {
  double maxHeight = 0;
  _pidLeftMotorController.SetReference((maxHeight+2), rev::ControlType::kSmartMotion);
  _pidRightMotorController.SetReference(-(maxHeight+2), rev::ControlType::kSmartMotion);
}

void SubClimber::Retract() {
  double minHeight = 35;
  _pidLeftMotorController.SetReference((minHeight-10), rev::ControlType::kSmartMotion);
  _pidRightMotorController.SetReference(-(minHeight-10), rev::ControlType::kSmartMotion);
}

void SubClimber::Rotate() {
_solTilter.Set(frc::DoubleSolenoid::kForward);
}

void SubClimber::Stow() {
  _solTilter.Set(frc::DoubleSolenoid::kReverse);
}

bool SubClimber::IsTopPressed() {
  return _lmtTop.Get();
}
bool SubClimber::IsBottomPressed() {
  return _lmtBottom.Get();
}