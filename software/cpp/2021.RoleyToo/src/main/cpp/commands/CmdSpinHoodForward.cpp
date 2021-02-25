// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdSpinHoodForward.h"

CmdSpinHoodForward::CmdSpinHoodForward(SubTurret* subTurret) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subTurret = subTurret;
}

// Called when the command is initially scheduled.
void CmdSpinHoodForward::Initialize() {
  _subTurret->SetHood(0.1);
}

// Called repeatedly when this Command is scheduled to run
void CmdSpinHoodForward::Execute() {}

// Called once the command ends or is interrupted.
void CmdSpinHoodForward::End(bool interrupted) {
  _subTurret->SetHood(0);
}

// Returns true when the command should end.
bool CmdSpinHoodForward::IsFinished() {
  return false;
}
