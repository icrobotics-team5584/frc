/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CmdSpit.h"
#include "../Robot.h"

CmdSpit::CmdSpit(bool slow) {
	_slow = slow;
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CmdSpit::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdSpit::Execute() {
	if (_slow) {
		Robot::subIntake->Out(0.5);
	} else {
		Robot::subIntake->Out();
	}

}

// Make this return true when this Command no longer needs to run execute()
bool CmdSpit::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdSpit::End() {
	Robot::subIntake->Stop();

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdSpit::Interrupted() {
	End();
}
