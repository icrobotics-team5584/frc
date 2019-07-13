/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdArmToFloor.h"

CmdArmToFloor::CmdArmToFloor() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subEncodedArm.get());
}

// Called just before this Command runs the first time
void CmdArmToFloor::Initialize() {
  Robot::subEncodedArm->ConfigTalon();
}

// Called repeatedly when this Command is scheduled to run
void CmdArmToFloor::Execute() {
  Robot::subEncodedArm->SetPosition(-angle);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdArmToFloor::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdArmToFloor::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdArmToFloor::Interrupted() {
  Robot::subEncodedArm->BrakeState(Robot::subEncodedArm->COAST);
}
