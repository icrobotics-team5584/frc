// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdColourSpinLeft.h"

CmdColourSpinLeft::CmdColourSpinLeft(SubColorWheel* subColorWheel) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(subColorWheel);
  _subColorWheel = subColorWheel;
}


// Called when the command is initially scheduled.
void CmdColourSpinLeft::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdColourSpinLeft::Execute() {}

// Called once the command ends or is interrupted.
void CmdColourSpinLeft::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdColourSpinLeft::IsFinished() {
  return false;
}
