/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdDrive.h"
#include "Robot.h"

CmdDrive::CmdDrive() {
  Requires(Robot::subDriveBase.get());
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CmdDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdDrive::Execute() {
  Robot::subDriveBase->Drive(Robot::m_oi.getJoystickY(), Robot::m_oi.getJoystickX());
}

// Make this return true when this Command no longer needs to run execute()
bool CmdDrive::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdDrive::End() {
  Robot::subDriveBase->Drive(0,0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdDrive::Interrupted() {
  End();
}
