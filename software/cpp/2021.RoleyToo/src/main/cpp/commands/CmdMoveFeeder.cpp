// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdMoveFeeder.h"

CmdMoveFeeder::CmdMoveFeeder(SubStorage* subStorage) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subStorage = subStorage;
}

// Called when the command is initially scheduled.
void CmdMoveFeeder::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdMoveFeeder::Execute() {
  _subStorage->MoveFeeder(SubStorage::Forward, _speed);
}

// Called once the command ends or is interrupted.
void CmdMoveFeeder::End(bool interrupted) {
  _subStorage->MoveFeeder(SubStorage::Forward, 0);
}

// Returns true when the command should end.
bool CmdMoveFeeder::IsFinished() {
  return false;
}
