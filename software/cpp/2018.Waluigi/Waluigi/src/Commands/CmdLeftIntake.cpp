/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CmdLeftIntake.h"
#include "../Robot.h"

CmdLeftIntake::CmdLeftIntake() {
	Requires(Robot::subIntake.get());
}

// Called just before this Command runs the first time
void CmdLeftIntake::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdLeftIntake::Execute() {
	Robot::subIntake->LeftIntake(Robot::oi->GetLeftAxis());
}

// Make this return true when this Command no longer needs to run execute()
bool CmdLeftIntake::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdLeftIntake::End() {
	Robot::subIntake->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdLeftIntake::Interrupted() {
	End();
}
