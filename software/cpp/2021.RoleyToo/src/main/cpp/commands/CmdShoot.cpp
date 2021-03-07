// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdShoot.h"

CmdShoot::CmdShoot(SubStorage* subStorage, SubTurret* subTurret) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subStorage = subStorage;
  _subTurret = subTurret;
}

void CmdShoot::StopEverythingAndPanic() {
  _subStorage->MoveFeeder(SubStorage::Forward, 0);
  _subStorage->Move(SubStorage::Forward, 0);
  _subTurret->SetTurret(0);
}

// Called when the command is initially scheduled.
void CmdShoot::Initialize() {
  _subTurret->SetReady(true); //Remove this once limelight code works
}

// Called repeatedly when this Command is scheduled to run
void CmdShoot::Execute() {

  if (_subTurret->IsReady()) {
    _subStorage->MoveFeeder(SubStorage::Forward, FeederSpeed);
    _subStorage->Move(SubStorage::Forward, StorageSpeed);
    FlywheelPIDOutput = _turretPID.Calculate(_subTurret->GetFlywheelRPM(), FlywheelRPMTarget);
    _subTurret->SetFlywheel(FlywheelPIDOutput);
  }
  else {
    StopEverythingAndPanic();
  }

}

// Called once the command ends or is interrupted.
void CmdShoot::End(bool interrupted) {
  StopEverythingAndPanic();
}

// Returns true when the command should end.
bool CmdShoot::IsFinished() {
  return false;
}
