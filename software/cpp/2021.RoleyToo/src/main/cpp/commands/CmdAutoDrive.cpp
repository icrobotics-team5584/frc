// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdAutoDrive.h"

CmdAutoDrive::CmdAutoDrive(SubDriveBase* subDriveBase, Autonomous* autonomous, double startX, double startY, 
                           double endX, double endY, double endHeading, double cenX, double cenY, 
                           PIDk PIDconstants, double speed, double endSpeed, PIDk pidSpeed){
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(subDriveBase);
  _subDriveBase = subDriveBase;
  _autonomous = autonomous;
  _startX = startX;
  _startY = startY;
  _endX = endX;
  _endY = endY;
  _endHeading = endHeading;
  _cenX = cenX;
  _cenY = cenY;
  _PIDconstants = PIDconstants;
  _speed = speed;
  _endSpeed = endSpeed;
  _pidSpeed = pidSpeed;
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
  return _autonomous->end(_endX, _endY, _endHeading, _speed);
}
