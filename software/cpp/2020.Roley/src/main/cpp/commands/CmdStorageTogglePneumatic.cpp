/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdStorageTogglePneumatic.h"
#include "subsystems/SubStorage.h"
#include "Robot.h"

CmdStorageTogglePneumatic::CmdStorageTogglePneumatic() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CmdStorageTogglePneumatic::Initialize() {
  Robot::subStorage->Expand();
}

// Called repeatedly when this Command is scheduled to run
void CmdStorageTogglePneumatic::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdStorageTogglePneumatic::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdStorageTogglePneumatic::End() {
  Robot::subStorage->Retract();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdStorageTogglePneumatic::Interrupted() {
  End();
}
