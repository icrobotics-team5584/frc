// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdSpinTurretLeft.h"

CmdSpinTurretLeft::CmdSpinTurretLeft(SubTurret* subTurret) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subTurret = subTurret;
}

// Called when the command is initially scheduled.
void CmdSpinTurretLeft::Initialize() {
  _subTurret->SetTurret(-frc::SmartDashboard::GetNumber("Turret Speed", 0));
}

// Called repeatedly when this Command is scheduled to run
void CmdSpinTurretLeft::Execute() {}

// Called once the command ends or is interrupted.
void CmdSpinTurretLeft::End(bool interrupted) {
  _subTurret->SetTurret(0);
}

// Returns true when the command should end.
bool CmdSpinTurretLeft::IsFinished() {
  return false;
}
