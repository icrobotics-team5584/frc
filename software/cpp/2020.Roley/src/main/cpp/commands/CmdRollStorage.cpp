/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdRollStorage.h"
#include "Robot.h"

CmdRollStorage::CmdRollStorage() {
  Requires(Robot::subStorage.get());
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CmdRollStorage::Initialize() {
  Robot::subStorage->Forward();
}

// Called repeatedly when this Command is scheduled to run
void CmdRollStorage::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdRollStorage::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdRollStorage::End() {
  Robot::subStorage->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdRollStorage::Interrupted() {
  End();
}
