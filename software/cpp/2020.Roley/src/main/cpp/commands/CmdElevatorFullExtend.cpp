/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdElevatorFullExtend.h"

#include "Robot.h"

CmdElevatorFullExtend::CmdElevatorFullExtend() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subClimber.get());

}

// Called just before this Command runs the first time
void CmdElevatorFullExtend::Initialize() {
  Robot::subClimber->ElevatorExtendMax();
}

// Called repeatedly when this Command is scheduled to run
void CmdElevatorFullExtend::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdElevatorFullExtend::IsFinished() { return true; }

// Called once after isFinished returns true
void CmdElevatorFullExtend::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdElevatorFullExtend::Interrupted() {
  End();
}
