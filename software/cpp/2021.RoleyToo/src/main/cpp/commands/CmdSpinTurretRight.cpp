// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdSpinTurretRight.h"

CmdSpinTurretRight::CmdSpinTurretRight(SubTurret* subTurret) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subTurret = subTurret;
}

// Called when the command is initially scheduled.
void CmdSpinTurretRight::Initialize() {
  _subTurret->SetTurret(frc::SmartDashboard::GetNumber("Turret Speed", 0));
}

// Called repeatedly when this Command is scheduled to run
void CmdSpinTurretRight::Execute() {}

// Called once the command ends or is interrupted.
void CmdSpinTurretRight::End(bool interrupted) {
  _subTurret->SetTurret(0);
}

// Returns true when the command should end.
bool CmdSpinTurretRight::IsFinished() {
  return false;
}
