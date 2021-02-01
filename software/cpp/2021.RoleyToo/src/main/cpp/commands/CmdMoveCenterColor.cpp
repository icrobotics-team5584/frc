// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdMoveCenterColor.h"

CmdMoveCenterColor::CmdMoveCenterColor(SubColorWheel* subColorWheel) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(subColorWheel);
  _subColorWheel = subColorWheel;
}

// Called when the command is initially scheduled.
void CmdMoveCenterColor::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdMoveCenterColor::Execute() {
  _subColorWheel->SpinColorWheel(40);
}

// Called once the command ends or is interrupted.
void CmdMoveCenterColor::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdMoveCenterColor::IsFinished() {
  return _subColorWheel->CheckSetPoint();
}
