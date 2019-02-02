/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdCloseIntakeFingers.h"
#include "Robot.h"
#include <frc/WPILib.h>

CmdCloseIntakeFingers::CmdCloseIntakeFingers() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subPanelAffector.get());
}

// Called just before this Command runs the first time
void CmdCloseIntakeFingers::Initialize() {
  Robot::subPanelAffector->RetractFingers();
}

// Called repeatedly when this Command is scheduled to run
void CmdCloseIntakeFingers::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdCloseIntakeFingers::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdCloseIntakeFingers::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdCloseIntakeFingers::Interrupted() {}
