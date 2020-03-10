/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdElevaterExtendMin.h"

#include "Robot.h"

CmdElevaterExtendMin::CmdElevaterExtendMin() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::subClimber.get());
}

// Called just before this Command runs the first time
void CmdElevaterExtendMin::Initialize() {
  Robot::subClimber->EnablePID();
  Robot::subClimber->ElevaterExtendMin();
}

// Called repeatedly when this Command is scheduled to run
void CmdElevaterExtendMin::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdElevaterExtendMin::IsFinished() { return true; }

// Called once after isFinished returns true
void CmdElevaterExtendMin::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdElevaterExtendMin::Interrupted() {
  End();
}
