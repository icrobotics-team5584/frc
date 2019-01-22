/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdSeekPath.h"
#include "Robot.h"

CmdSeekPath::CmdSeekPath() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subDriveBase.get());
  posEncoderGyro.reset(new PosEncoderGyro);
  dvoTank.reset(new DvoTank);
  pathFollower.reset(new PathFollower("", posEncoderGyro, dvoTank));
}

// Called just before this Command runs the first time
void CmdSeekPath::Initialize() {
  pathFollower->reset();

}

// Called repeatedly when this Command is scheduled to run
void CmdSeekPath::Execute() {
  pathFollower->followPath();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdSeekPath::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdSeekPath::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdSeekPath::Interrupted() {}
