// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdAutoFeedStop.h"

CmdAutoFeedStop::CmdAutoFeedStop(SubStorage* subStorage) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subStorage = subStorage;
}

// Called when the command is initially scheduled.
void CmdAutoFeedStop::Initialize() {
  _subStorage->Feed(0);
}

// Called repeatedly when this Command is scheduled to run
void CmdAutoFeedStop::Execute() {}

// Called once the command ends or is interrupted.
void CmdAutoFeedStop::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdAutoFeedStop::IsFinished() {
  return true;
}
