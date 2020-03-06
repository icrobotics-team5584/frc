/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdManualStorage.h"
#include "Robot.h"


CmdManualStorage::CmdManualStorage() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subStorage.get());
}

// Called just before this Command runs the first time
void CmdManualStorage::Initialize() {
  Robot::subStorage->Backward();
}

// Called repeatedly when this Command is scheduled to run
void CmdManualStorage::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdManualStorage::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdManualStorage::End() {
  Robot::subStorage->Stop();

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdManualStorage::Interrupted() {
  End();
}
