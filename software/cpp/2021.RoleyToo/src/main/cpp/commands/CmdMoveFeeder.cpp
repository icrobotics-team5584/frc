// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdMoveFeeder.h"

CmdMoveFeeder::CmdMoveFeeder(SubStorage* subStorage, SubStorage::Direction direction, double speed) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subStorage = subStorage;
  _speed = speed;
  _direction = direction;
}

// Called when the command is initially scheduled.
void CmdMoveFeeder::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdMoveFeeder::Execute() {
  std::cout << "CmdMoveFeeder::Execute() Run." << "\n";
  _subStorage->MoveFeeder(_direction, _speed);
}

// Called once the command ends or is interrupted.
void CmdMoveFeeder::End(bool interrupted) {
  _subStorage->MoveFeeder(_direction, 0);
}

// Returns true when the command should end.
bool CmdMoveFeeder::IsFinished() {
  return false;
}
