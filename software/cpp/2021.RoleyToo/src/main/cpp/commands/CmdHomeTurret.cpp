// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdHomeTurret.h"

CmdHomeTurret::CmdHomeTurret(SubTurret* subTurret) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(subTurret);
  _subTurret = subTurret;
}

// Called when the command is initially scheduled.
void CmdHomeTurret::Initialize() { }

// Called repeatedly when this Command is scheduled to run
void CmdHomeTurret::Execute() {
  if (_state == 0)
  {
    if (_subTurret->GetTurretAngle() < 1 && _subTurret->GetTurretAngle() > -1)
    {
      _subTurret->SetTurret(0);
      _state = 1;
    }
    else
    {
      _subTurret->SetTurret(std::clamp(_turretPID.Calculate(_subTurret->GetTurretAngle(), 0), -0.25, 0.25));
    }
    
  }
  else if (_state == 1)
  {
    if (_subTurret->GetRightLimit())
    {
      _subTurret->ResetTurretEncoder(6);
      _subTurret->SetTurretHomed(true);
      _state = 2;
    }
    else
    {
      _subTurret->SetTurret(_homingSpeed);
    }
  }
}

// Called once the command ends or is interrupted.
void CmdHomeTurret::End(bool interrupted) {
  _subTurret->SetTurret(0);
}

// Returns true when the command should end.
bool CmdHomeTurret::IsFinished() {
  return _state == 2;
}
