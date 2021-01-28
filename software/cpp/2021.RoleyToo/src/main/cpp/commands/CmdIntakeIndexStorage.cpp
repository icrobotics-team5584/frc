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
  _intakeSwitch = false; // change this false to intake get sensor()
  if (_intakeSwitch) {
    _index = true;
  }

  //INDEX BALLS HERE
  if (_index) {
    _subStorage->Move(SubStorage::Direction::Forward, 0.0);
    for (int i=0; i <= 5; i++) {
      //move encoder to pos
      _pidOutput = 1;
      while (_pidOutput != 0) {
        _target = 40; //distance from one divider to another
        _pidOutput = _storagePID.Calculate(_target - _subStorage->GetEncoder());
        _subStorage->Move(SubStorage::Direction::Forward, _pidOutput);
      }
      _subStorage->ResetEncoder();

      //check if ball is loaded
      _indexSwitch = _subStorage->GetSensor(SubStorage::Sensors::Index);
      if (_indexSwitch) {
        _subStorage->SetBallCount(_subStorage->GetBallCount() + 1);
      }
    }

    _index = false;
  }

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
