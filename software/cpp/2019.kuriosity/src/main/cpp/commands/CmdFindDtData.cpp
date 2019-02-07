/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdFindDtData.h"
#include "Robot.h"
#include <fstream>

CmdFindDtData::CmdFindDtData() : file("/home/lvuser/drivetraindata.txt") {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void CmdFindDtData::Initialize() {
  Robot::subDriveBase->zeroEncoders();
  file << "velocity, acceleration, jerk, left encoder value" << std::endl;
  // Drive at full speed
  timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void CmdFindDtData::Execute() {
  Robot::subDriveBase->drive(1,0);
  currentDisplacement = Robot::subDriveBase->getDistanceTravelled();
  currentTime = timer.Get();
  //velocity = dDisplacement/dTime
  currentVelocity = (currentDisplacement - oldDisplacement) / (currentTime - oldTime);

  //acceleration = dVelocity/dTime
  currentAcceleration = (currentVelocity - oldVelocity) / (currentTime - oldTime);

  //jerk = dAcceleration/dTime
  jerk = (currentAcceleration - oldAcceleration) / (currentTime - oldTime);

  //make all the current variables 'old' variables in preparation for the next loop
  oldTime = currentTime;
  oldVelocity = currentVelocity;
  oldAcceleration = currentAcceleration;
  file << currentVelocity << ", " << currentAcceleration << ", " << jerk << "," << Robot::subDriveBase->getRawLeftEncoder() << std::endl;
}

// Make this return true when this Command no longer needs to run execute()
bool CmdFindDtData::IsFinished() {
  return false;
 }

// Called once after isFinished returns true
void CmdFindDtData::End() {
  file.close();
  Robot::subDriveBase->drive(0,0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdFindDtData::Interrupted() {}
