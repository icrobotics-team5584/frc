// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdClimbToPos.h"
#include "subsystems/SubClimber.h"

CmdClimbToPos::CmdClimbToPos(SubClimber* subClimber, double target) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subClimber = subClimber;
  _target = target;
}

// Called when the command is initially scheduled.
void CmdClimbToPos::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdClimbToPos::Execute() {}

// Called once the command ends or is interrupted.
void CmdClimbToPos::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdClimbToPos::IsFinished() {
  return false;
}