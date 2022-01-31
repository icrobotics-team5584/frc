// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdAutoDrive.h"

CmdAutoDrive::CmdAutoDrive(SubDriveBase* subDriveBase, Autonomous* autonomous, PIDAutoConfig _PIDConfig){
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(subDriveBase);
  _subDriveBase = subDriveBase;
  _autonomous = autonomous;
  _startX = _PIDConfig.startX;
  _startY = _PIDConfig.startY;
  _endX = _PIDConfig.endX;
  _endY = _PIDConfig.endY;
  _endHeading = _PIDConfig.endHeading;
  _cenX = _PIDConfig.cenX;
  _cenY = _PIDConfig.cenY;
  _PIDconstants = _PIDConfig.PIDconstants;
  _speed = _PIDConfig.speed;
  _endSpeed = _PIDConfig.endSpeed;
  _pidSpeed = _PIDConfig.pidSpeed;
}

// Called when the command is initially scheduled.
void CmdAutoDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdAutoDrive::Execute() {
  driveInput = _autonomous->autoDrive(_startX, _startY, _endX, _endY, _endHeading, _cenX, _cenY,  _pidSpeed, _PIDconstants, _speed, _endSpeed);
  _subDriveBase->drive(driveInput.speed, driveInput.steering);
}

// Called once the command ends or is interrupted.
void CmdAutoDrive::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdAutoDrive::IsFinished() {
  return _autonomous->end(_endX, _endY, _startX, _startY, _speed);
}
