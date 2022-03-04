// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdExtendClimber.h"

CmdExtendClimber::CmdExtendClimber(SubClimber* subClimber) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subClimber = subClimber;
}

// Called when the command is initially scheduled.
void CmdExtendClimber::Initialize() {
  _subClimber->Extend();
}

// Called repeatedly when this Command is scheduled to run
void CmdExtendClimber::Execute() {
}

// Called once the command ends or is interrupted.
void CmdExtendClimber::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdExtendClimber::IsFinished() {
  return false;
}
