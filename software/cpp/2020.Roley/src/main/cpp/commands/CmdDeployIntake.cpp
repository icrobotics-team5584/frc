/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdDeployIntake.h"
#include "Robot.h"

CmdDeployIntake::CmdDeployIntake() {
  // Doesnt requre storage or intake because this needs to be used at the same time as CmdIntake,
  // which does require those subsystems.
}

// Called just before this Command runs the first time
void CmdDeployIntake::Initialize() {
  Robot::subIntake->Deploy();
  Robot::subStorage->Expand();
}

// Called repeatedly when this Command is scheduled to run
void CmdDeployIntake::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdDeployIntake::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdDeployIntake::End() {
  Robot::subIntake->Retract();
  Robot::subStorage->Retract();

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdDeployIntake::Interrupted() {End();}
