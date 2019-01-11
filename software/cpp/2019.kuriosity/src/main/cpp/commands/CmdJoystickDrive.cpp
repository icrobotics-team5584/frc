/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdJoystickDrive.h"
#include "Robot.h"

CmdJoystickDrive::CmdJoystickDrive() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void CmdJoystickDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdJoystickDrive::Execute() {
  double x = Robot::_oi->controller->GetX();
  double y = Robot::_oi->controller->GetY();
  Robot::subDriveBase->drive(y,x);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdJoystickDrive::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdJoystickDrive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdJoystickDrive::Interrupted() {}
