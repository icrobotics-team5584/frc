/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdStorageRetract.h"
#include "subsystems/SubStorage.h"
#include "Robot.h"
#include <iostream>


CmdStorageRetract::CmdStorageRetract() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CmdStorageRetract::Initialize() {
  std::cout << "------------------------------------------------storage retract init" << std::endl;

}

// Called repeatedly when this Command is scheduled to run
void CmdStorageRetract::Execute() {
  Robot::subStorage->Retract();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdStorageRetract::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdStorageRetract::End() {
  std::cout << "------------------------------------------------storage retract end" << std::endl;

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdStorageRetract::Interrupted() {}
