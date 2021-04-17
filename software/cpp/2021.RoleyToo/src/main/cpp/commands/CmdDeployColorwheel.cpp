// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdDeployColorwheel.h"

CmdDeployColorwheel::CmdDeployColorwheel(SubColorWheel* subColorWheel) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(subColorWheel);
  _subColorWheel = subColorWheel;
}

// Called when the command is initially scheduled.
void CmdDeployColorwheel::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdDeployColorwheel::Execute() {}

// Called once the command ends or is interrupted.
void CmdDeployColorwheel::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdDeployColorwheel::IsFinished() {
  return false;
}
