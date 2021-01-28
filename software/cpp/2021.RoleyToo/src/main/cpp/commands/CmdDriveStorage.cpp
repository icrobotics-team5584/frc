// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdDriveStorage.h"

CmdDriveStorage::CmdDriveStorage(SubStorage* subStorage, SubStorage::Direction direction, double speed) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subStorage = subStorage;
  _direction = direction;
  _speed = speed;
}

// Called when the command is initially scheduled.
void CmdDriveStorage::Initialize() {
  _subStorage->Move(_direction, _speed);
}

// Called repeatedly when this Command is scheduled to run
void CmdDriveStorage::Execute() {}

// Called once the command ends or is interrupted.
void CmdDriveStorage::End(bool interrupted) {
  _subStorage->Move(SubStorage::Direction::Forward, 0);
}

// Returns true when the command should end.
bool CmdDriveStorage::IsFinished() {
  return false;
}
