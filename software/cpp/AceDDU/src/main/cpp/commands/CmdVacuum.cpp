/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdVacuum.h"
#include "Robot.h"
CmdVacuum::CmdVacuum() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::subClimber.get());
  std::cout << "CmdVacuum Construct" << std::endl;
}

// Called just before this Command runs the first time
void CmdVacuum::Initialize() {
  Robot::subClimber->VacuumIn();
  std::cout << "CmdVacuum Init" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void CmdVacuum::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdVacuum::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdVacuum::End() {
  Robot::subClimber->VacuumOut();
  std::cout << "CmdVacuum End" << std::endl;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdVacuum::Interrupted() {
  End();
}
