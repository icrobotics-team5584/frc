// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdShoot.h"
#include "frc/smartdashboard/SmartDashboard.h"

CmdShoot::CmdShoot(SubStorage* subStorage, SubTurret* subTurret) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subStorage = subStorage;
  _subTurret = subTurret;
  //frc::SmartDashboard::PutNumber("Shooter Speedies", 0);
  frc::SmartDashboard::PutNumber("Turret P", 0.0007);
  frc::SmartDashboard::PutNumber("Turret I", 0);
  frc::SmartDashboard::PutNumber("Turret D", 0.00004);
  frc::SmartDashboard::PutNumber("Turret F", 0.6);
}

void CmdShoot::StopEverythingAndPanic() {
  //_subStorage->MoveFeeder(SubStorage::Forward, 0);
  _subStorage->Move(SubStorage::Forward, 0);
  _subTurret->SetFlywheel(0);
}

// Called when the command is initially scheduled.
void CmdShoot::Initialize() {
  _subTurret->SetReady(true); //Remove this once limelight code works
  frc::SmartDashboard::PutData(&_turretPID);
}

// Called repeatedly when this Command is scheduled to run
void CmdShoot::Execute() {
  _turretPID.SetPID(frc::SmartDashboard::GetNumber("Turret P", 0), frc::SmartDashboard::GetNumber("Turret I", 0), frc::SmartDashboard::GetNumber("Turret D", 0));

  //_subStorage->MoveFeeder(SubStorage::Forward, FeederSpeed);
  _subStorage->Move(SubStorage::Forward, StorageSpeed);
  FlywheelPIDOutput = _turretPID.Calculate(_subTurret->GetFlywheelRPM(), FlywheelRPMTarget);

  FlywheelPIDOutput += frc::SmartDashboard::GetNumber("Turret F", 0);
  frc::SmartDashboard::PutNumber("current flywheel power", FlywheelPIDOutput);
  _subTurret->SetFlywheel(FlywheelPIDOutput);
  //_subTurret->SetFlywheel(frc::SmartDashboard::GetNumber("Shooter Speedies", 0));
}

// Called once the command ends or is interrupted.
void CmdShoot::End(bool interrupted) {
  StopEverythingAndPanic();
}

// Returns true when the command should end.
bool CmdShoot::IsFinished() {
  return false;
}
