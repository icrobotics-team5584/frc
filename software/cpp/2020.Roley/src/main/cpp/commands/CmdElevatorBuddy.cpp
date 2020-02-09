/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdElevatorBuddy.h"

#include "Robot.h"

CmdElevatorBuddy::CmdElevatorBuddy() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subClimber.get());
}

// Called just before this Command runs the first time
void CmdElevatorBuddy::Initialize() {
  Robot::subClimber->ElevatorExtendBuddy();
}

// Called repeatedly when this Command is scheduled to run
void CmdElevatorBuddy::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdElevatorBuddy::IsFinished() { return Robot::subClimber->IsAtTarget(); }

// Called once after isFinished returns true
void CmdElevatorBuddy::End() {
  Robot::subClimber->RatchetsEngage();
  Robot::subClimber->DisablePID();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdElevatorBuddy::Interrupted() {
  End();
}
