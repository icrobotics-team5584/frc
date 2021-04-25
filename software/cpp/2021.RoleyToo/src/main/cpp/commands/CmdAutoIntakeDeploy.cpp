// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdAutoIntakeDeploy.h"

CmdAutoIntakeDeploy::CmdAutoIntakeDeploy(SubIntake* subIntake) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(subIntake);
  _subIntake = subIntake;
}

// Called when the command is initially scheduled.
void CmdAutoIntakeDeploy::Initialize() {
  _subIntake->Deploy();
}

// Called repeatedly when this Command is scheduled to run
void CmdAutoIntakeDeploy::Execute() {}

// Called once the command ends or is interrupted.
void CmdAutoIntakeDeploy::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdAutoIntakeDeploy::IsFinished() {
  return true;
}
