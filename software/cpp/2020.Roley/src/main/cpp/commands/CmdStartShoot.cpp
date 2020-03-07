/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdStartShoot.h"
#include "Robot.h"
#include <iostream>

CmdStartShoot::CmdStartShoot() {
  Requires(Robot::subShooter.get());
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CmdStartShoot::Initialize() {
  std::cout << "------------------------------------------------start shoot init" << std::endl;

  Robot::subShooter->PowerShoot();
}

// Called repeatedly when this Command is scheduled to run
void CmdStartShoot::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdStartShoot::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdStartShoot::End() {
  std::cout << "------------------------------------------------start shoot end" << std::endl;

  //Does not end using for command group
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdStartShoot::Interrupted() {}
