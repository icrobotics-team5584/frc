// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdAutoFeederFeed.h"

CmdAutoFeederFeed::CmdAutoFeederFeed(SubStorage* subStorage) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subStorage = subStorage;
  AddRequirements(_subStorage);
}

// Called when the command is initially scheduled.
void CmdAutoFeederFeed::Initialize() {
  _subStorage->Feed(1);
}

// Called repeatedly when this Command is scheduled to run
void CmdAutoFeederFeed::Execute() {}

// Called once the command ends or is interrupted.
void CmdAutoFeederFeed::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdAutoFeederFeed::IsFinished() {
  return true;
}
