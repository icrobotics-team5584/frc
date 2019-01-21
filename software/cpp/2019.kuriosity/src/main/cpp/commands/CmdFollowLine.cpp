/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdFollowLine.h"
#include "Robot.h"
#include "frc/WPILib.h"
#include <iostream>

CmdFollowLine::CmdFollowLine() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void CmdFollowLine::Initialize() {
  angle = 0;
}

// Called repeatedly when this Command is scheduled to run
void CmdFollowLine::Execute() {
  SmartDashboard::PutNumber("angle", angle);
  Robot::subDriveBase->drive(drivePower, angle);
  //if both sensors are seeing the line, drive foward because we know that the front of the robot is parallel with the loading station
  if (Robot::subDriveBase->isRightClsOnLine() && Robot::subDriveBase->isLeftClsOnLine()) {
    angle = 0;
  }
  //if only the right colour sensor sees the line, turn left because the robot is not centred
  else if (Robot::subDriveBase->isRightClsOnLine()) {

    angle = 0.5;
  }
  //the last possible case is that only the left colour sensor is seeing the line. We make it turn right in an attempt to centre it.
  else if (Robot::subDriveBase->isLeftClsOnLine()) {
    angle = -0.5;
  }
}

// Make this return true when this Command no longer needs to run execute()
bool CmdFollowLine::IsFinished() {
  std::cout << "Running isFinished()" << std::endl;
  double range = Robot::subDriveBase->getDistanceToObstical();
  std::cout << "range " << range << std::endl;
  return (range < 100) or (range > 1700);
}

// Called once after isFinished returns true
void CmdFollowLine::End() {
  std::cout << "Ending CmdFollowLine" << std::endl;
  Robot::subDriveBase->drive(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdFollowLine::Interrupted() {
  End();
}
