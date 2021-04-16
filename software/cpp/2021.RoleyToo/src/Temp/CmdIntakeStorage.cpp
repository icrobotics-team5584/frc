// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdIntakeStorage.h"
#include <frc/smartdashboard/SmartDashboard.h>

CmdIntakeStorage::CmdIntakeStorage(SubStorage* subStorage) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subStorage = subStorage;
}

// Called when the command is initially scheduled.
void CmdIntakeStorage::Initialize() {
  _timer.Reset();
  _timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void CmdIntakeStorage::Execute() {
  frc::SmartDashboard::PutNumber("Storage Current", _subStorage->GetStorageCurrent());

  if (_timer.Get() > 1.5) {
    if (_subStorage->GetStorageCurrent() > 15) {
      _overcurrenttime.Start();
      if (_overcurrenttime.Get() > 0.7) {
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

  double StorageP = 0.00017;
  double StorageI = 0;
  double StorageD = 0;
  double StorageFF = 0.135;
  double storageRPM = _subStorage->GetEncoderSpeed();
  _storagePID.SetP(StorageP);
  _storagePID.SetI(StorageI);
  _storagePID.SetD(StorageD);

  double power = 0;
  if (_currentdir == SubStorage::Direction::Forward) {
    power = std::clamp(_storagePID.Calculate(storageRPM, setpoint) + StorageFF, -1.0, 1.0);
  }
  else {
    power = std::clamp(_storagePID.Calculate(storageRPM, -setpoint) - StorageFF, -1.0, 1.0);
  }
  frc::SmartDashboard::PutNumber("Storage RPM", storageRPM);
  frc::SmartDashboard::PutNumber("storage power", power);
  _subStorage->Move(SubStorage::Direction::Forward, power);
}

// Called once the command ends or is interrupted.
void CmdIntakeStorage::End(bool interrupted) {
  _subStorage->Move(SubStorage::Direction::Forward, 0.0);
  _subStorage->ScheduleIndexing(true);
}

// Returns true when the command should end.
bool CmdIntakeStorage::IsFinished() {
  return false;
}
