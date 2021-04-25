// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdClimbManual.h"
#include "frc/smartdashboard/SmartDashboard.h"

CmdClimbManual::CmdClimbManual(SubClimber* subClimber) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subClimber = subClimber;
  frc::SmartDashboard::PutNumber("Climb Retract Speed", 0);
}

// Called when the command is initially scheduled.
void CmdClimbManual::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdClimbManual::Execute() {
  _subClimber->Retract(frc::SmartDashboard::GetNumber("Climb Retract Speed", 0.4), SubClimber::left);
  _subClimber->Retract(frc::SmartDashboard::GetNumber("Climb Retract Speed", 0.4), SubClimber::right);
}

// Called once the command ends or is interrupted.
void CmdClimbManual::End(bool interrupted) {
  _subClimber->Retract(0.0, SubClimber::left);
  _subClimber->Retract(0.0, SubClimber::right);
}

// Returns true when the command should end.
bool CmdClimbManual::IsFinished() {
  return false;
}
