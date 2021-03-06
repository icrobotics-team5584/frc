/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdAutoStorage.h"
#include "Robot.h"

CmdAutoStorage::CmdAutoStorage() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
 // Requires(Robot::subStorage.get());
}

// Called just before this Command runs the first time
void CmdAutoStorage::Initialize() {
  Robot::subStorage->SetSpeed(1.0);
  Robot::subStorage->BottomRollerForward();
}

// Called repeatedly when this Command is scheduled to run
void CmdAutoStorage::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdAutoStorage::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdAutoStorage::End() {
  Robot::subStorage->Stop();
  Robot::subStorage->BottomRollerStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdAutoStorage::Interrupted() {
  End();
}
