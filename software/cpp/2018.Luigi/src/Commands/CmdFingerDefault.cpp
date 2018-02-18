/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CmdFingerDefault.h"

CmdFingerDefault::CmdFingerDefault() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CmdFingerDefault::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdFingerDefault::Execute() {
	switch (Robot::subFinger->GetSwitchCase()){
	case 0:
	break;
	case 1:
		SetTimeout(0.5);
		Robot::subFinger->FingerDown();
	break;
	}

}

// Make this return true when this Command no longer needs to run execute()
bool CmdFingerDefault::IsFinished() {
	return IsTimedOut();
}

// Called once after isFinished returns true
void CmdFingerDefault::End() {
	Robot::subFinger->FingerDefaultStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdFingerDefault::Interrupted() {

}
