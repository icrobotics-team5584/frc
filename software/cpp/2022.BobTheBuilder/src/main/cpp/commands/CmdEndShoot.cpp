// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdEndShoot.h"

CmdEndShoot::CmdEndShoot(SubStorage* subStorage, SubIntake* subIntake, SubShooter* subShooter) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subShooter = subShooter;
  _subStorage = subStorage;
  _subIntake = subIntake;
  AddRequirements(_subShooter);
  AddRequirements(_subStorage);
  AddRequirements(_subIntake);
}

// Called when the command is initially scheduled.
void CmdEndShoot::Initialize() {
  _subStorage->Stop();
  _subStorage->ExtendStopper(); 
  _subIntake->Retract();
}

// Called repeatedly when this Command is scheduled to run
void CmdEndShoot::Execute() {}

// Called once the command ends or is interrupted.
void CmdEndShoot::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdEndShoot::IsFinished() {
  return true;
}
