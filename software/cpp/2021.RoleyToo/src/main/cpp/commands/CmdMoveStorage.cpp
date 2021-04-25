// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdMoveStorage.h"

#include <frc/smartdashboard/SmartDashboard.h>

CmdMoveStorage::CmdMoveStorage(SubStorage* subStorage, int antiJamRPM) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subStorage = subStorage;
  _antiJamRPM = antiJamRPM;
}

// Called when the command is initially scheduled.
void CmdMoveStorage::Initialize() {
  frc::SmartDashboard::PutNumber("Storage Anti-Jam RPM Target", _antiJamRPM);

  _timer.Reset();
  _timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void CmdMoveStorage::Execute() {

  _antiJamRPM = frc::SmartDashboard::GetNumber("Storage Anti-Jam RPM Target", _antiJamRPM);

  if (_timer.Get() > 0.7) {
    /* WARNING: Long Code Ahead!
       If storage is slower than minimum velocity, switch direction of storage and reset timer */
    if ((_subStorage->GetEncoderSpeed() < _antiJamRPM and _subStorage->GetEncoderSpeed() > 0) || (_subStorage->GetEncoderSpeed() > -_antiJamRPM and _subStorage->GetEncoderSpeed() < 0)) {
      _overcurrenttime.Start();
      if (_overcurrenttime.Get() > 0.3) {
        switch (_currentdir) {
          case SubStorage::Direction::Forward:
            _currentdir = SubStorage::Direction::Backward;
            break;
          case SubStorage::Direction::Backward:
            _currentdir = SubStorage::Direction::Forward;
            break;
        }
        _timer.Reset();
        _timer.Start();
      }
    }
    else {
      _overcurrenttime.Stop();
      _overcurrenttime.Reset();
    }
  }

  double storageRPM = _subStorage->GetEncoderSpeed();

  if (_currentdir == SubStorage::Direction::Forward) {
    power = std::clamp(_storagePID.Calculate(storageRPM, Setpoint) + StorageF, -1.0, 1.0);
  }
  else {
    power = std::clamp(_storagePID.Calculate(storageRPM, -Setpoint) - StorageF, -1.0, 1.0);
  }
  frc::SmartDashboard::PutNumber("Storage RPM", storageRPM);
  frc::SmartDashboard::PutNumber("storage power", power);
  _subStorage->Move(SubStorage::Direction::Forward, power);
}

// Called once the command ends or is interrupted.
void CmdMoveStorage::End(bool interrupted) {
  _subStorage->Move(SubStorage::Direction::Forward, 0.0);
  _subStorage->ScheduleIndexing(true);
}

// Returns true when the command should end.
bool CmdMoveStorage::IsFinished() {
  return false;
}
