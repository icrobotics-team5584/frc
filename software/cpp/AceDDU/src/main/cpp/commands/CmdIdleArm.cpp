/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdIdleArm.h"

CmdIdleArm::CmdIdleArm() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  
  Requires(Robot::subEncodedArm.get());

}

// Called just before this Command runs the first time
void CmdIdleArm::Initialize() {

  //turn off motors
  Robot::subEncodedArm->setSpeed(0);

  //initiate the brake
  Robot::subEncodedArm->BrakeState(Robot::subEncodedArm->BRAKE);

}

// Called repeatedly when this Command is scheduled to run
void CmdIdleArm::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdIdleArm::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdIdleArm::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdIdleArm::Interrupted() {

  //relase the brake
  Robot::subEncodedArm->BrakeState(Robot::subEncodedArm->COAST);

}
