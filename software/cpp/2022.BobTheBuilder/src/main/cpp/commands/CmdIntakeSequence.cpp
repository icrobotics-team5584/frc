// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdIntakeSequence.h"

CmdIntakeSequence::CmdIntakeSequence(SubIntake* subIntake, SubStorage* subStorage) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subIntake = subIntake;
  _subStorage = subStorage;
}

// Called when the command is initially scheduled.
void CmdIntakeSequence::Initialize() {
  _subIntake->Extend();
  _subIntake->Intake();
  _subStorage->In();
  _subStorage->ExtendStopper();
}

// Called repeatedly when this Command is scheduled to run
void CmdIntakeSequence::Execute() {}

// Called once the command ends or is interrupted.
void CmdIntakeSequence::End(bool interrupted) {
  _subIntake->Retract();
  _subIntake->Stop();
  _subStorage->DelayStop();
}

// Returns true when the command should end.
bool CmdIntakeSequence::IsFinished() {
  return false;
}
