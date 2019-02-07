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
  drivePower = 0.6;
}

// Called repeatedly when this Command is scheduled to run
void CmdSeekRocketCargo::Execute() {

  Robot::subDriveBase->drive(drivePower, 0);
  //Robot::subDriveBase->positionPID((1 - Robot::subDriveBase->getDistanceTravelled()) / 0.000078);
  //frc::SmartDashboard::PutNumber("error value", (1 - Robot::subDriveBase->getDistanceTravelled()) / 0.000078);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdSeekRocketCargo::IsFinished() { return Robot::subDriveBase->clsBackRightDetected(); }

// Called once after isFinished returns true
void CmdSeekRocketCargo::End() {
  Robot::subDriveBase->drive(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdSeekRocketCargo::Interrupted() {}
