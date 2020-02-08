/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdEngageClimberRatchets.h"

CmdEngageClimberRatchets::CmdEngageClimberRatchets() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subClimber.get());
}

// Called just before this Command runs the first time
void CmdEngageClimberRatchets::Initialize() {
  Robot::subClimber->RatchetsEngage();
}

// Called repeatedly when this Command is scheduled to run
void CmdEngageClimberRatchets::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdEngageClimberRatchets::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdEngageClimberRatchets::End() {
  Robot::subClimber->RatchetsDisengage();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdEngageClimberRatchets::Interrupted() {
  End();
}
