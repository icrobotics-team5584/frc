/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdSeekPath.h"
#include "Robot.h"
#include "pathfinder.h"

CmdSeekPath::CmdSeekPath() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subDriveBase.get());
  posEncoderGyro.reset(new PosEncoderGyro);
  dvoTank.reset(new DvoTank);
  Segment * seg = Robot::subDriveBase->generatePath();
  int pathLength = Robot::subDriveBase->getPathLength();
  pathFollower.reset(new PathFollower(seg, pathLength, posEncoderGyro, dvoTank));
}

// Called just before this Command runs the first time
void CmdSeekPath::Initialize() {
  pathFollower->reset();
  Robot::subDriveBase->zeroEncoders();
  Robot::subDriveBase->setTalControlMode(ControlMode::PercentOutput);
  Robot::subDriveBase->velocityPIDConfig();
  scaleFactor = wheelCircumference/4096;
  // SmartDashboard::PutBoolean("Running CmdSeekpath", true);
}

// Called repeatedly when this Command is scheduled to run
void CmdSeekPath::Execute() {
  //pathFollower->followPath();
  double leftVelocity = 1.5 / scaleFactor / 10;
  double rightVelocity = -1.5 / scaleFactor / 10;
  SmartDashboard::PutNumber("PID velocity", leftVelocity);
  Robot::subDriveBase->tankDriveVelocity(leftVelocity, rightVelocity);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdSeekPath::IsFinished() { 
  return false;
  return pathFollower->isFinished();
}

// Called once after isFinished returns true
void CmdSeekPath::End() {
  SmartDashboard::PutBoolean("Running CmdSeekpath", false);
  Robot::subDriveBase->tankDriveVelocity(0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdSeekPath::Interrupted() {}
