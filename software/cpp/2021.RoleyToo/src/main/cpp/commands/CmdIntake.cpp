// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdIntake.h"
#include "frc/smartdashboard/SmartDashboard.h"

CmdIntake::CmdIntake(SubStorage* subStorage, SubIntake* subIntake) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subStorage = subStorage;
  _subIntake = subIntake;
  //frc::SmartDashboard::PutData("Storage PID", &_storagePID);
  frc::SmartDashboard::PutNumber("Storage Setpoint", Setpoint);
  frc::SmartDashboard::PutNumber("Storage P", StorageP);
  frc::SmartDashboard::PutNumber("Storage I", StorageI);
  frc::SmartDashboard::PutNumber("Storage D", StorageD);
  frc::SmartDashboard::PutNumber("Storage FF", StorageF);
}

// Called when the command is initially scheduled.
void CmdIntake::Initialize() {
  _timer.Reset();
  _timer.Start();

  _delayIntake.Reset();
  _delayIntake.Start();
}

// Called repeatedly when this Command is scheduled to run
void CmdIntake::Execute() {

  frc::SmartDashboard::PutNumber("Storage Current", _subStorage->GetStorageCurrent());
  
  if (_delayIntake.Get() > 0.7)
  {
    _subIntake->Intake();
  }
  else
  {
    _subIntake->Outtake();
  }
  

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

  double storageF = frc::SmartDashboard::GetNumber("Storage FF", StorageF);

  double storageRPM = _subStorage->GetEncoderSpeed();
  double setpoint = frc::SmartDashboard::GetNumber("Storage Setpoint", Setpoint);
  _storagePID.SetP(frc::SmartDashboard::GetNumber("Storage P", StorageP));
  _storagePID.SetI(frc::SmartDashboard::GetNumber("Storage I", StorageI));
  _storagePID.SetD(frc::SmartDashboard::GetNumber("Storage D", StorageD));

  double power = 0;
  if (_currentdir == SubStorage::Direction::Forward) {
    power = std::clamp(_storagePID.Calculate(storageRPM, setpoint) + storageF, -1.0, 1.0);
  }
  else {
    power = std::clamp(_storagePID.Calculate(storageRPM, -setpoint) - storageF, -1.0, 1.0);
  }
  frc::SmartDashboard::PutNumber("Storage RPM", storageRPM);
  frc::SmartDashboard::PutNumber("storage power", power);
  _subStorage->Move(SubStorage::Direction::Forward, power);
}

// Called once the command ends or is interrupted.
void CmdIntake::End(bool interrupted) {
  std::cout << "running CmdIntake::End()" << std::endl;
  _subIntake->Stop();
  _subStorage->Move(SubStorage::Direction::Forward, 0.0);
  _subStorage->ScheduleIndexing(true);
}

// Returns true when the command should end.
bool CmdIntake::IsFinished() {
  return false;
}
