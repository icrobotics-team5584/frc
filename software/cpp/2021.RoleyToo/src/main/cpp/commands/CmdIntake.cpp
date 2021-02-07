// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdIntake.h"

CmdIntake::CmdIntake(SubStorage* subStorage, SubIntake* subIntake) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subStorage = subStorage;
  _subIntake = subIntake;
}

// Called when the command is initially scheduled.
void CmdIntake::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdIntake::Execute() {
  _subIntake->Deploy();
  _subIntake->Intake();
  _subStorage->Move(SubStorage::Direction::Forward, 0.2);
}

// Called once the command ends or is interrupted.
void CmdIntake::End(bool interrupted) {
  _subIntake->Stop();
  _subStorage->Move(SubStorage::Direction::Forward, 0.0);
  _subStorage->ScheduleIndexing(true);
  _subIntake->Retract();
}

// Returns true when the command should end.
bool CmdIntake::IsFinished() {
  return false;
}
