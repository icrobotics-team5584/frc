/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdStopShoot.h"
#include "Robot.h"
#include <iostream>


CmdStopShoot::CmdStopShoot() {
  Requires(Robot::subShooter.get());
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CmdStopShoot::Initialize() {
  //does not start using for command group
  std::cout << "------------------------------------------------stop shoot init" << std::endl;

}

// Called repeatedly when this Command is scheduled to run
void CmdStopShoot::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdStopShoot::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdStopShoot::End() {
  std::cout << "------------------------------------------------stop shoot end" << std::endl;
  Robot::subShooter->Stop();

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdStopShoot::Interrupted() {
  End();
}
