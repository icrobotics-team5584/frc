// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdRetractColorWheel.h"

CmdRetractColorWheel::CmdRetractColorWheel(SubColorWheel* subColorWheel) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(subColorWheel);
  _subColorWheel = subColorWheel;
}
// Called when the command is initially scheduled.
void CmdRetractColorWheel::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdRetractColorWheel::Execute() {
  _subColorWheel->RetractColorWheel();
}

// Called once the command ends or is interrupted.
void CmdRetractColorWheel::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdRetractColorWheel::IsFinished() {
  return false;
}
