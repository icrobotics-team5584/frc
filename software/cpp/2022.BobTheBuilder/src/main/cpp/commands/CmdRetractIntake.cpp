// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdRetractIntake.h"

CmdRetractIntake::CmdRetractIntake(SubIntake* subIntake) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subIntake = subIntake;
}

// Called when the command is initially scheduled.
void CmdRetractIntake::Initialize() {
  _subIntake->Retract();
}

// Called repeatedly when this Command is scheduled to run
void CmdRetractIntake::Execute() {}

// Called once the command ends or is interrupted.
void CmdRetractIntake::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdRetractIntake::IsFinished() {
  return true;
}
