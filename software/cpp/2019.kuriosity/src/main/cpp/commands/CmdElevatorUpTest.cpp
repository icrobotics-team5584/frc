/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdElevatorUpTest.h"

CmdElevatorUpTest::CmdElevatorUpTest() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subElevator.get());
}

// Called just before this Command runs the first time
void CmdElevatorUpTest::Initialize() {
  Robot::subElevator->TestingUp();
}

// Called repeatedly when this Command is scheduled to run
void CmdElevatorUpTest::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdElevatorUpTest::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdElevatorUpTest::End() {
  Robot::subElevator->TestingStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdElevatorUpTest::Interrupted() {
  End();
}
