/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdShooterShoot.h"
#include "Robot.h"

CmdShooterShoot::CmdShooterShoot() {
  //Requires(Robot::subShooter.get());
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CmdShooterShoot::Initialize() {
  

}

// Called repeatedly when this Command is scheduled to run
void CmdShooterShoot::Execute() {
  Robot::subShooter->Shoot();

}

// Make this return true when this Command no longer needs to run execute()
bool CmdShooterShoot::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdShooterShoot::End() {
  Robot::subShooter->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdShooterShoot::Interrupted() {
  End();
}
