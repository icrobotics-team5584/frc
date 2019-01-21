/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/CmdBrake.h"
#include "Robot.h"

CmdBrake::CmdBrake() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
// Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void CmdBrake::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void CmdBrake::Execute() {
  Robot::subDriveBase->brakeRobot();
}
bool CmdBrake::IsFinished() {}

// Called once after command times out
void CmdBrake::End() {
  Robot::subDriveBase->drive(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdBrake::Interrupted() {}

