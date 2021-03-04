// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdAutoTurn.h"

CmdAutoTurn::CmdAutoTurn(SubDriveBase* subDriveBase, Autonomous* autonomous, PIDk PIDconstants, double angle) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(subDriveBase);
  _autonomous = autonomous;
  _subDriveBase = subDriveBase;
  _PIDconstants = PIDconstants;
  _angle = angle;
}

// Called when the command is initially scheduled.
void CmdAutoTurn::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdAutoTurn::Execute() {
  driveInput = _autonomous->turnTo(_angle, _PIDconstants);
  _subDriveBase->drive(driveInput.speed, driveInput.steering);
}

// Called once the command ends or is interrupted.
void CmdAutoTurn::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdAutoTurn::IsFinished() {
  return _autonomous->turnToEnd(_angle);
}
