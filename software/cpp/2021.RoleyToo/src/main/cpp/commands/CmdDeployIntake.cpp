// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdDeployIntake.h"

CmdDeployIntake::CmdDeployIntake(SubIntake* subIntake, bool retract) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(subIntake);
  _subIntake = subIntake;
  _retract = retract;
}

// Called when the command is initially scheduled.
void CmdDeployIntake::Initialize() {
  _subIntake->Deploy();
}

// Called repeatedly when this Command is scheduled to run
void CmdDeployIntake::Execute() {}

// Called once the command ends or is interrupted.
void CmdDeployIntake::End(bool interrupted) {
  if (_retract)
  {
    _subIntake->Retract();
  }
}

// Returns true when the command should end.
bool CmdDeployIntake::IsFinished() {
  return false;
}
