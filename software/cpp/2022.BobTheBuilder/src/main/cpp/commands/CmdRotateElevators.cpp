// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdRotateElevators.h"

CmdRotateElevators::CmdRotateElevators(SubClimber* subClimber) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subClimber = subClimber;
}

// Called when the command is initially scheduled.
void CmdRotateElevators::Initialize() {
_subClimber->Rotate();
}

// Called repeatedly when this Command is scheduled to run  
void CmdRotateElevators::Execute() {}

// Called once the command ends or is interrupted.
void CmdRotateElevators::End(bool interrupted) {
  _subClimber->Stow();
}

// Returns true when the command should end.
bool CmdRotateElevators::IsFinished() {
  return false;
}
