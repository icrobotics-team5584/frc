// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdToggleShootingPosition.h"

CmdToggleShootingPosition::CmdToggleShootingPosition(SubShooter* subShooter) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subShooter = subShooter;
}

// Called when the command is initially scheduled.
void CmdToggleShootingPosition::Initialize() {
  _subShooter->TogglePosition();
}

// Called repeatedly when this Command is scheduled to run
void CmdToggleShootingPosition::Execute() {}

// Called once the command ends or is interrupted.
void CmdToggleShootingPosition::End(bool interrupted) {
  _subShooter->TogglePosition();
}

// Returns true when the command should end.
bool CmdToggleShootingPosition::IsFinished() {
  return false;
}
