/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdDeployIntakeOnly.h"
#include "Robot.h"
#include <iostream>


CmdDeployIntakeOnly::CmdDeployIntakeOnly() {
  Requires(Robot::subIntake.get());
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CmdDeployIntakeOnly::Initialize() {
  std::cout << "------------------------------------------------intake only init" << std::endl;

  Robot::subIntake->Deploy();
}

// Called repeatedly when this Command is scheduled to run
void CmdDeployIntakeOnly::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdDeployIntakeOnly::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdDeployIntakeOnly::End() {
  std::cout << "------------------------------------------------deploy intake only end" << std::endl;

  Robot::subStorage->Retract();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdDeployIntakeOnly::Interrupted() {
  End();
}
