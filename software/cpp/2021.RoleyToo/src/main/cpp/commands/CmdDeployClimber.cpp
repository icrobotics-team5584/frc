// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdDeployClimber.h"

CmdDeployClimber::CmdDeployClimber(SubClimber* subClimber) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subClimber = subClimber;
}

// Called when the command is initially scheduled.
void CmdDeployClimber::Initialize() {
  _subClimber->SetPneumatic(SubClimber::Solenoids::Deploy, frc::DoubleSolenoid::Value::kForward);
}

// Called repeatedly when this Command is scheduled to run
void CmdDeployClimber::Execute() {}

// Called once the command ends or is interrupted.
void CmdDeployClimber::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdDeployClimber::IsFinished() {
  return false;
}
