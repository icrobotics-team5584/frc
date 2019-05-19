/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdIntakeOutakeStop.h"
#include "Robot.h"

CmdIntakeOutakeStop::CmdIntakeOutakeStop() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subIntakeOutake.get());
  // Requires(Robot::subRollerIntake.get());
  Requires(Robot::subPanelAffector.get());
}

// Called just before this Command runs the first time
void CmdIntakeOutakeStop::Initialize() {
  Robot::subIntakeOutake->Stop();
  // Robot::subRollerIntake->Stop();
  Robot::subPanelAffector->RetractFingers();
}

// Called repeatedly when this Command is scheduled to run
void CmdIntakeOutakeStop::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdIntakeOutakeStop::IsFinished() { return true; }

// Called once after isFinished returns true
void CmdIntakeOutakeStop::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdIntakeOutakeStop::Interrupted() {}
