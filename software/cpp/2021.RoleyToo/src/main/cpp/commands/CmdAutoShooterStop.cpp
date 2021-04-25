// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdAutoShooterStop.h"

CmdAutoShooterStop::CmdAutoShooterStop(SubTurret* subTurret) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subTurret = subTurret;
}

// Called when the command is initially scheduled.
void CmdAutoShooterStop::Initialize() {
  _subTurret->SetFlywheel(0);
}

// Called repeatedly when this Command is scheduled to run
void CmdAutoShooterStop::Execute() {}

// Called once the command ends or is interrupted.
void CmdAutoShooterStop::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdAutoShooterStop::IsFinished() {
  return true;
}
