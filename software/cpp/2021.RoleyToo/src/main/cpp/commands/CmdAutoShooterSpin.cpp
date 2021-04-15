// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdAutoShooterSpin.h"

CmdAutoShooterSpin::CmdAutoShooterSpin(SubTurret* subTurret) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subTurret = subTurret;
  AddRequirements(_subTurret);
}

// Called when the command is initially scheduled.
void CmdAutoShooterSpin::Initialize() {
  _subTurret->SetFlywheel(1);
}

// Called repeatedly when this Command is scheduled to run
void CmdAutoShooterSpin::Execute() {}

// Called once the command ends or is interrupted.
void CmdAutoShooterSpin::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdAutoShooterSpin::IsFinished() {
  return true;
}
