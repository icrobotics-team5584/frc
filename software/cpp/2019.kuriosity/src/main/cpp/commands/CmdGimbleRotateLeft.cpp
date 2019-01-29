/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdGimbleRotateLeft.h"
#include "Robot.h"

CmdGimbleRotateLeft::CmdGimbleRotateLeft() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subGimble.get());
}

// Called just before this Command runs the first time
void CmdGimbleRotateLeft::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdGimbleRotateLeft::Execute() {
  Robot::subGimble->OverridePID(true);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdGimbleRotateLeft::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdGimbleRotateLeft::End() {
  Robot::subGimble->stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdGimbleRotateLeft::Interrupted() {
  End();
}
