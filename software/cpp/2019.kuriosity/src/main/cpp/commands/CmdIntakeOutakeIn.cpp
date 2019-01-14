/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdIntakeOutakeIn.h"
#include "Robot.h"

CmdIntakeOutakeIn::CmdIntakeOutakeIn() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::subIntakeOutake.get());
  //Requires(Robot::subRollerIntake.get());
}

// Called just before this Command runs the first time
void CmdIntakeOutakeIn::Initialize() {
  Robot::subIntakeOutake->Intake();
  Robot::subRollerIntake->RollerIn();
}

// Called repeatedly when this Command is scheduled to run
void CmdIntakeOutakeIn::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdIntakeOutakeIn::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdIntakeOutakeIn::End() {
  Robot::subIntakeOutake->Stop();
  Robot::subRollerIntake->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdIntakeOutakeIn::Interrupted() {
  End();
}
