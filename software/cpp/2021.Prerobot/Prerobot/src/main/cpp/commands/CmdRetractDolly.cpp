// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdRetractDolly.h"

CmdRetractDolly::CmdRetractDolly(SubDrivebase* subDrivebase) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(subDrivebase);
  _subDrivebase = subDrivebase;
}

// Called when the command is initially scheduled.
void CmdRetractDolly::Initialize() {
  _subDrivebase->DollyRetract();
}

// Called repeatedly when this Command is scheduled to run
void CmdRetractDolly::Execute() {}

// Called once the command ends or is interrupted.
void CmdRetractDolly::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdRetractDolly::IsFinished() {
  return false;
}
