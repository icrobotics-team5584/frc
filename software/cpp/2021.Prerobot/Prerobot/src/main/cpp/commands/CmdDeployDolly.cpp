// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdDeployDolly.h"

CmdDeployDolly::CmdDeployDolly(SubDrivebase* subDrivebase) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(subDrivebase);
  _subDrivebase = subDrivebase;
}

// Called when the command is initially scheduled.
void CmdDeployDolly::Initialize() {
  _subDrivebase->DollyDeploy();
}

// Called repeatedly when this Command is scheduled to run
void CmdDeployDolly::Execute() {}

// Called once the command ends or is interrupted.
void CmdDeployDolly::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdDeployDolly::IsFinished() {
  return false;
}
