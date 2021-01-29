// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdIndexStorage.h"

CmdIndexStorage::CmdIndexStorage(SubStorage* subStorage) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subStorage = subStorage;
}

// Called when the command is initially scheduled.
void CmdIndexStorage::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdIndexStorage::Execute() {
  if (_subStorage->NeedsIndexing()) {

    //Index here.
    std::cout << "Storage Indexing." << "\n";

    //Don't index again until next requested.
    _subStorage->ScheduleIndexing(false);
  }
}

// Called once the command ends or is interrupted.
void CmdIndexStorage::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdIndexStorage::IsFinished() {
  return false;
}
