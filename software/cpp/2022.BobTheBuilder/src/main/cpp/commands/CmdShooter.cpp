// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdShooter.h"


CmdShooter::CmdShooter(SubShooter* subShooter) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subShooter = subShooter;
}

// Called when the command is initially scheduled.
void CmdShooter::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdShooter::Execute() {
  _subShooter -> Shoot;
}; 
// Called once the command ends or is interrupted.
void CmdShooter::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdShooter::IsFinished() {
  return false;
}
