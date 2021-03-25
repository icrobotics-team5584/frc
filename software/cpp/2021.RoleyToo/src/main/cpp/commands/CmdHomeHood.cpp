// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdHomeHood.h"
#include "frc/smartdashboard/SmartDashboard.h"

CmdHomeHood::CmdHomeHood(SubTurret* subTurret) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subTurret = subTurret;
}

// Called when the command is initially scheduled.
void CmdHomeHood::Initialize() {
  
}

// Called repeatedly when this Command is scheduled to run
void CmdHomeHood::Execute() {
  frc::SmartDashboard::PutBoolean("Hood Limit", _subTurret->GetHoodLimit());
  if (_subTurret->GetHoodLimit()) {
    _subTurret->SetHood(0.1);
  }
  else {
    _subTurret->SetHood(0);
    _subTurret->ResetHoodEncoder();
  }
}

// Called once the command ends or is interrupted.
void CmdHomeHood::End(bool interrupted) {
  _subTurret->SetHood(0);
}

// Returns true when the command should end.
bool CmdHomeHood::IsFinished() {
  return false;
}
