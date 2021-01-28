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
  std::cout << "it started" << "\n";
  _subTurret->SetTurret(0.3);
}

// Called repeatedly when this Command is scheduled to run
void CmdHomeTurret::Execute() {
  std::cout << _subTurret->GetLeftLimit() << "\n";
  if (_subTurret->GetLeftLimit()) {
    std::cout << "Its running" << "\n";
    _subTurret->ResetTurretEncoder();
    while(_subTurret->GetTurretAngle() < 10) {
      _subTurret->SetTurret(-0.3);
    }
    targetReached = true;
  }
}

// Called once the command ends or is interrupted.
void CmdHomeTurret::End(bool interrupted) {
  _subTurret->SetTurret(0);
}

// Returns true when the command should end.
bool CmdHomeTurret::IsFinished() {
  return targetReached;
}
