// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdMotorDriver.h"

CmdMotorDriver::CmdMotorDriver(SubMotorDriver* subMotorDriver) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(subMotorDriver);
  _subMotorDriver = subMotorDriver;
}

// Called when the command is initially scheduled.
void CmdMotorDriver::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdMotorDriver::Execute() {
  _subMotorDriver->Drive(0.5);
}

// Called once the command ends or is interrupted.
void CmdMotorDriver::End(bool interrupted) {
  _subMotorDriver->Drive(0);
}

// Returns true when the command should end.
bool CmdMotorDriver::IsFinished() {
  return false;
}
