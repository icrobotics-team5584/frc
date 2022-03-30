// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdStopShooter.h"

CmdStopShooter::CmdStopShooter(SubShooter* subShooter) {
  // Use addRequirements() here to declare subsystem dependencies.
 _subShooter = subShooter;
}

// Called when the command is initially scheduled.
void CmdStopShooter::Initialize() {
  _subShooter -> Stop();
}

// Called repeatedly when this Command is scheduled to run
void CmdStopShooter::Execute() {}

// Called once the command ends or is interrupted.
void CmdStopShooter::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdStopShooter::IsFinished() {
  return true;
}
