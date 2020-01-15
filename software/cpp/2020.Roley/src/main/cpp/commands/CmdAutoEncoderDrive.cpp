/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include "Robot.h"
#include "commands/CmdAutoEncoderDrive.h"
#include <iostream>
CmdAutoEncoderDrive::CmdAutoEncoderDrive() {
  Requires(Robot::subDriveBase.get());

  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CmdAutoEncoderDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdAutoEncoderDrive::Execute() {
  Robot::subDriveBase->autoEncoderDrive(-1.7);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdAutoEncoderDrive::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdAutoEncoderDrive::End() {
  Robot::subDriveBase->drive(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdAutoEncoderDrive::Interrupted() {
  End();
}
