/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdGimbleRotateRight.h"
#include "Robot.h"
#include "subsystems/SubGimble.h"

CmdGimbleRotateRight::CmdGimbleRotateRight() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subGimble.get());
}

// Called just before this Command runs the first time
void CmdGimbleRotateRight::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdGimbleRotateRight::Execute() {
  Robot::subGimble->OverridePID(false);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdGimbleRotateRight::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdGimbleRotateRight::End() {
  Robot::subGimble->stop(2);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdGimbleRotateRight::Interrupted() {
  End();
}
