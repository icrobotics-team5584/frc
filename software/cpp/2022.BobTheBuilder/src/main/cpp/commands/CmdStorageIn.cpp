// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdStorageIn.h"
#include "subsystems/SubStorage.h"

CmdStorageIn::CmdStorageIn(SubStorage* subStorage) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subStorage = subStorage;
}

// Called when the command is initially scheduled.
void CmdStorageIn::Initialize() {
  _subStorage->In();
}

// Called repeatedly when this Command is scheduled to run
void CmdStorageIn::Execute() {}

// Called once the command ends or is interrupted.
void CmdStorageIn::End(bool interrupted) {
  _subStorage->Stop();
}

// Returns true when the command should end.
bool CmdStorageIn::IsFinished() {
  return false;
}
