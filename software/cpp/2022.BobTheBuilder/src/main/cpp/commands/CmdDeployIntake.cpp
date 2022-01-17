// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdDeployIntake.h"

CmdDeployIntake::CmdDeployIntake(SubIntake* subIntake) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subIntake = subIntake;
}

// Called when the command is initially scheduled.
void CmdDeployIntake::Initialize() {
  _subIntake->Extend();
}

// Called repeatedly when this Command is scheduled to run
void CmdDeployIntake::Execute() {}

// Called once the command ends or is interrupted.
void CmdDeployIntake::End(bool interrupted) {
  _subIntake->Retract();
}

// Returns true when the command should end.
bool CmdDeployIntake::IsFinished() {
  return false;
}
