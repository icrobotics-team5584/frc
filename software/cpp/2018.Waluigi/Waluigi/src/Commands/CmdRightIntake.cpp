/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CmdRightIntake.h"
#include "../Robot.h"

CmdRightIntake::CmdRightIntake() {
	Requires(Robot::subIntake.get());
}

// Called just before this Command runs the first time
void CmdRightIntake::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdRightIntake::Execute() {
	Robot::subIntake->RightIntake(Robot::oi->GetRightAxis());
}

// Make this return true when this Command no longer needs to run execute()
bool CmdRightIntake::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdRightIntake::End() {
	Robot::subIntake->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdRightIntake::Interrupted() {
	End();
}
