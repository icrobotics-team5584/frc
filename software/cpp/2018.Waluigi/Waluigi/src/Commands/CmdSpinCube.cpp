/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CmdSpinCube.h"
#include "../Robot.h"

CmdSpinCube::CmdSpinCube() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::subIntake.get());
}

// Called just before this Command runs the first time
void CmdSpinCube::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdSpinCube::Execute() {
	Robot::subIntake->Spin();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdSpinCube::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdSpinCube::End() {
	Robot::subIntake->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdSpinCube::Interrupted() {
	End();
}
