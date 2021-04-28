// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdManualClimbL.h"

CmdManualClimbL::CmdManualClimbL(SubClimber* subClimber) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subClimber = subClimber;
}

// Called when the command is initially scheduled.
void CmdManualClimbL::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdManualClimbL::Execute() {
  std::cout << "CmdManualClimbL" << std::endl;
  _subClimber->Retract(0.8, SubClimber::left);
}

// Called once the command ends or is interrupted.
void CmdManualClimbL::End(bool interrupted) {
  _subClimber->Retract(0, SubClimber::left);
}

// Returns true when the command should end.
bool CmdManualClimbL::IsFinished() {
  return false;
}
