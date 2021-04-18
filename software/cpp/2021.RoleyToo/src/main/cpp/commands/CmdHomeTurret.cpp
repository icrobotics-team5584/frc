// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdHomeTurret.h"

CmdHomeTurret::CmdHomeTurret(SubTurret* subTurret) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subTurret = subTurret;
}

// Called when the command is initially scheduled.
void CmdHomeTurret::Initialize() {
  if (!_subTurret->GetRightLimit())
  {
    //_subTurret->SetTurret(_homingSpeed);
  }
}

// Called repeatedly when this Command is scheduled to run
void CmdHomeTurret::Execute() {}

// Called once the command ends or is interrupted.
void CmdHomeTurret::End(bool interrupted) {
  _subTurret->SetTurret(0);
  _subTurret->ResetTurretEncoder();
}

// Returns true when the command should end.
bool CmdHomeTurret::IsFinished() {
  //return _subTurret->GetRightLimit();
  return true;
}
