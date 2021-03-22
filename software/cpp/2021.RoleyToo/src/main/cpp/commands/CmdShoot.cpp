// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdShoot.h"
#include "frc/smartdashboard/SmartDashboard.h"

CmdShoot::CmdShoot(SubStorage* subStorage, SubTurret* subTurret) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subStorage = subStorage;
  //frc::SmartDashboard::PutNumber("Shooter Speedies", 0);

}

void CmdShoot::StopEverythingAndPanic() {
  _subStorage->MoveFeeder(SubStorage::Forward, 0);
}

// Called when the command is initially scheduled.
void CmdShoot::Initialize() {
  //_subTurret->SetReady(true); //Remove this once limelight code works
}

// Called repeatedly when this Command is scheduled to run
void CmdShoot::Execute() {
  

    _subStorage->MoveFeeder(SubStorage::Forward, 1.0);
    std::cout << "Fuck\n";
    

}

// Called once the command ends or is interrupted.
void CmdShoot::End(bool interrupted) {
  _subStorage->MoveFeeder(SubStorage::Forward, 0.0);
  std::cout << "Not Fuck\n";
}

// Returns true when the command should end.
bool CmdShoot::IsFinished() {
  return false;
}
