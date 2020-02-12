/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdAutoShoot.h"
#include "Robot.h"

CmdAutoShoot::CmdAutoShoot() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  //Requires()
}

// Called just before this Command runs the first time
void CmdAutoShoot::Initialize() {
 // Robot::subShooter->PowerShoot();
}

// Called repeatedly when this Command is scheduled to run
void CmdAutoShoot::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdAutoShoot::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdAutoShoot::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdAutoShoot::Interrupted() {}
