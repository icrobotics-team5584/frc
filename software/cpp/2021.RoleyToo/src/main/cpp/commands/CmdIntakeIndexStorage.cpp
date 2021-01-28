// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdIntakeIndexStorage.h"

CmdIntakeIndexStorage::CmdIntakeIndexStorage(SubStorage* subStorage) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subStorage = subStorage;
}

// Called when the command is initially scheduled.
void CmdIntakeIndexStorage::Initialize() {
  //RUN INTAKE
  _subStorage->Move(SubStorage::Direction::Forward, 0.2);
}

// Called repeatedly when this Command is scheduled to run
void CmdIntakeIndexStorage::Execute() {
  //GET INTAKE LINE BREAK

  //INDEX BALLS HERE

  if (_subStorage->GetBallCount() >= 5) { //We shouldn't spin/intake if we already have five balls.
    _killCommand = true;
  }

}

// Called once the command ends or is interrupted.
void CmdIntakeIndexStorage::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdIntakeIndexStorage::IsFinished() {
  return _killCommand;
}
