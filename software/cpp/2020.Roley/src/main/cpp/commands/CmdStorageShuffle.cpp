/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdStorageShuffle.h"
#include "Robot.h"  

CmdStorageShuffle::CmdStorageShuffle() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subStorage.get());
}

// Called just before this Command runs the first time
void CmdStorageShuffle::Initialize() {
  Robot::subStorage->Backward();
}

// Called repeatedly when this Command is scheduled to run
void CmdStorageShuffle::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdStorageShuffle::IsFinished() { return !Robot::subStorage->lbrTopIsBlocked(); }

// Called once after isFinished returns true
void CmdStorageShuffle::End() {
  Robot::subStorage->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdStorageShuffle::Interrupted() {
  End();
}
