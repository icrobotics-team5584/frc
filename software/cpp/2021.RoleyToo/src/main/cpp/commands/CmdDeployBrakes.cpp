// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdDeployBrakes.h"

CmdDeployBrakes::CmdDeployBrakes(SubClimber* subClimber) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subClimber = subClimber;
}

// Called when the command is initially scheduled.
void CmdDeployBrakes::Initialize() {
  _subClimber->SetPneumatic(0);
}

// Called repeatedly when this Command is scheduled to run
void CmdDeployBrakes::Execute() {}

// Called once the command ends or is interrupted.
void CmdDeployBrakes::End(bool interrupted) {
  _subClimber->SetPneumatic(1);
}

// Returns true when the command should end.
bool CmdDeployBrakes::IsFinished() {
  return false;
}
