// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdIntakeIndexStorage.h"

CmdIntakeIndexStorage::CmdIntakeIndexStorage(SubStorage* subStorage) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subStorage = subStorage;
}

// Called when the command is initially scheduled.
void CmdIntakeIndexStorage::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdIntakeIndexStorage::Execute() {

  _subStorage->Move(SubStorage::Direction::Forward, 0.2);

}

// Called once the command ends or is interrupted.
void CmdIntakeIndexStorage::End(bool interrupted) {
  _subStorage->Move(SubStorage::Direction::Forward, 0.0);
  _subStorage->ScheduleIndexing(true);
}

// Returns true when the command should end.
bool CmdIntakeIndexStorage::IsFinished() {
  return false;
}
