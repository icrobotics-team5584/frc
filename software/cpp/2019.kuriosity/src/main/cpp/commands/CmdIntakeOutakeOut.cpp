/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdIntakeOutakeOut.h"
#include "Robot.h"

CmdIntakeOutakeOut::CmdIntakeOutakeOut() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::subIntakeOutake.get());
  Requires(&(*Robot::subRollerIntake));
}

// Called just before this Command runs the first time
void CmdIntakeOutakeOut::Initialize() {
    Robot::subIntakeOutake->Outake();
    //Robot::subRollerIntake->RollerOut();
}

// Called repeatedly when this Command is scheduled to run
void CmdIntakeOutakeOut::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdIntakeOutakeOut::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdIntakeOutakeOut::End() {
  Robot::subIntakeOutake->Stop();
  Robot::subRollerIntake->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdIntakeOutakeOut::Interrupted() {
  End();
}
