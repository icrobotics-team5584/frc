// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdRetractClimber.h"

CmdRetractClimber::CmdRetractClimber(SubClimber* subClimber) {
  // Use addRequirements() here to declare subsystem dependencies.

  _subClimber = subClimber;}

// Called when the command is initially scheduled.
void CmdRetractClimber::Initialize() {
  _subClimber->Retract();
}

// Called repeatedly when this Command is scheduled to run
void CmdRetractClimber::Execute() {}

// Called once the command ends or is interrupted.
void CmdRetractClimber::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdRetractClimber::IsFinished() {
  return false;
}
