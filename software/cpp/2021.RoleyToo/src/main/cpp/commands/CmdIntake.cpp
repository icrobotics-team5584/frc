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
  frc::SmartDashboard::PutNumber("Storage Setpoint", 100);
  frc::SmartDashboard::PutNumber("Storage P", 0.2);
  frc::SmartDashboard::PutNumber("Storage I", 0.0);
  frc::SmartDashboard::PutNumber("Storage D", 0.0);
  frc::SmartDashboard::PutNumber("Storage FF", 0.0);
}

// Called when the command is initially scheduled.
void CmdIntake::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdIntake::Execute() {
  _subIntake->Deploy();
  _subIntake->Intake();

  double StorageP = frc::SmartDashboard::GetNumber("Storage P", 0);
  double StorageI = frc::SmartDashboard::GetNumber("Storage I", 0);
  double StorageD = frc::SmartDashboard::GetNumber("StorageD", 0);
  double StorageFF = frc::SmartDashboard::GetNumber("Storage FF", 0);
  double setpoint = frc::SmartDashboard::GetNumber("Storage Setpoint", 0);
  double storageRPM = _subStorage->GetEncoderSpeed();
  _storagePID.SetP(StorageP);
  _storagePID.SetI(StorageI);
  _storagePID.SetD(StorageD);

  double power = std::clamp(_storagePID.Calculate(storageRPM, setpoint) + StorageFF, -1.0, 1.0);
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
  _subIntake->Retract();
}

// Returns true when the command should end.
bool CmdIntake::IsFinished() {
  return false;
}
