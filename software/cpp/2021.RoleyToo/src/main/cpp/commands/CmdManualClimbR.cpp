// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdManualClimbR.h"

CmdManualClimbR::CmdManualClimbR(SubClimber* subClimber) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subClimber = subClimber;
}

// Called when the command is initially scheduled.
void CmdManualClimbR::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdManualClimbR::Execute() {
  _subClimber->Retract(0.8, SubClimber::right);
}

// Called once the command ends or is interrupted.
void CmdManualClimbR::End(bool interrupted) {
  std::cout << "CmdManualClimbR" << std::endl;
  _subClimber->Retract(0, SubClimber::right);
}

// Returns true when the command should end.
bool CmdManualClimbR::IsFinished() {
  return false;
}
