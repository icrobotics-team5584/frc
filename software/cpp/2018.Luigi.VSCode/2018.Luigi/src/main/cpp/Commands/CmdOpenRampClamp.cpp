/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CmdOpenRampClamp.h"
#include "Robot.h"

CmdOpenRampClamp::CmdOpenRampClamp() {
	Requires(Robot::subRamp.get());
}

// Called just before this Command runs the first time
void CmdOpenRampClamp::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdOpenRampClamp::Execute() {
	Robot::subRamp->OpenRampClamp();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdOpenRampClamp::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdOpenRampClamp::End() {
	Robot::subRamp->StopRamp();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdOpenRampClamp::Interrupted() {
	End();

}
