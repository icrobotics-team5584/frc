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

  switch (_commandState) {
    case Nothing:
      _subStorage->Move(SubStorage::Direction::Forward, 0.0);
      break;
    case Intake:
      _subStorage->Move(SubStorage::Direction::Forward, 0.2);
      if (_subStorage->GetSensor(SubStorage::Sensors::Intake)) {
        _loadTimer = 0;
        _commandState = LoadBall;
      }
      break;
      
    case LoadBall:
      _subStorage->Move(SubStorage::Direction::Forward, 0.2);
      _loadTimer++;
      if (_loadTimer > _loadLimit) {
        _subStorage->Move(SubStorage::Direction::Forward, 0.0);
        _commandState = IndexMoveFirst;
      }
      break;

    case IndexMoveFirst:
      //Check which position we're closest to
      //Spin to that position
      //If we're there, IndexTest.
      _indexCount = 0;
      break;

    case IndexMoveConsecutive:
      //Get StoragePosition
      //from that, get, and set the newStoragePosition
      //spin to newStoragePosition
      //if we're there, IndexTest.
      break;

    case IndexTest:
      //Index the storage
      if (_indexCount == 5) {
        _commandState = Intake;
      }
      else {
        _commandState = IndexMoveConsecutive;
      }
      break;

    case Exit:
      _commandState = Nothing;
      _stopCommand = true;
      break;
  }

}

// Called once the command ends or is interrupted.
void CmdIntakeIndexStorage::End(bool interrupted) {
  _subStorage->Move(SubStorage::Direction::Forward, 0.0);
}

// Returns true when the command should end.
bool CmdIntakeIndexStorage::IsFinished() {
  return _stopCommand;
}
