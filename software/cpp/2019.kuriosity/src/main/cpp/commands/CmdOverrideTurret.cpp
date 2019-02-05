/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdOverrideTurret.h"
#include "Robot.h"
#include <frc/WPILib.h>

CmdOverrideTurret::CmdOverrideTurret() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::subElevator.get());
//  Requires(Robot::SubGimble.get());
}

// Called just before this Command runs the first time
void CmdOverrideTurret::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdOverrideTurret::Execute() {
  	Robot::subElevator->Override(Robot::_oi->getJoystick0());
}

// Make this return true when this Command no longer needs to run execute()
bool CmdOverrideTurret::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdOverrideTurret::End() {
  Robot::subElevator->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdOverrideTurret::Interrupted() {
  End();
}
