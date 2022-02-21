// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdStorageOut.h"
#include "subsystems/SubStorage.h"

CmdStorageOut::CmdStorageOut(SubStorage* subStorage) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subStorage = subStorage;
}

// Called when the command is initially scheduled.
void CmdStorageOut::Initialize() {
  _subStorage->Out();
}

// Called repeatedly when this Command is scheduled to run
void CmdStorageOut::Execute() {}

// Called once the command ends or is interrupted.
void CmdStorageOut::End(bool interrupted) {
  _subStorage->Stop();
}

// Returns true when the command should end.
bool CmdStorageOut::IsFinished() {
  return false;
}
