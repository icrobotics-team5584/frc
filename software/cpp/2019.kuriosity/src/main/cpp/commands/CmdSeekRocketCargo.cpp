/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdSeekRocketCargo.h"

CmdSeekRocketCargo::CmdSeekRocketCargo() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void CmdSeekRocketCargo::Initialize() {
  driveStateRocket = SEARCHING;
  drivePower = 0.6;
  Robot::subDriveBase->pidPositionConfig();
}

// Called repeatedly when this Command is scheduled to run
void CmdSeekRocketCargo::Execute() {
  switch (driveStateRocket) {
    case SEARCHING:
      if(Robot::subDriveBase->frontHasReachedLine()) {
        driveStateRocket = REVERSING_TO_LINE;
      }
    case REVERSING_TO_LINE:
    Robot::subDriveBase->positionPID();
  }
}

// Make this return true when this Command no longer needs to run execute()
bool CmdSeekRocketCargo::IsFinished() { return Robot::subDriveBase->midHasReachedLine() and finishStage; }

// Called once after isFinished returns true
void CmdSeekRocketCargo::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdSeekRocketCargo::Interrupted() {}
