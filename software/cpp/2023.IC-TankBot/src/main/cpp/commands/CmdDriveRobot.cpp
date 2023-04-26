// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdDriveRobot.h"
#include "subsystems/SubDriveBase.h"

CmdDriveRobot::CmdDriveRobot(frc::XboxController* controller) {
  // Use addRequirements() here to declare subsystem dependencies.
  _XboxController = controller;
  AddRequirements(&SubDriveBase::GetInstance());
}

// Called when the command is initially scheduled.
void CmdDriveRobot::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdDriveRobot::Execute() {
  double speed = _XboxController -> GetLeftY();
  double turning = _XboxController -> GetLeftX();
  turning = turning * -1;
  double speedLimited = _stickYLimiter.Calculate(units::volt_t(speed)).value();

  SubDriveBase::GetInstance().drive(speedLimited, turning, false);
}

// Called once the command ends or is interrupted.
void CmdDriveRobot::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdDriveRobot::IsFinished() {
  return false;
}
