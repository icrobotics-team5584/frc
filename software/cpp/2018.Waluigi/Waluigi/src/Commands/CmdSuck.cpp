/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CmdSuck.h"

CmdSuck::CmdSuck() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CmdSuck::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdSuck::Execute() {
	Robot::subIntake->In();

}

// Make this return true when this Command no longer needs to run execute()
bool CmdSuck::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdSuck::End() {
	Robot::subIntake->Stop();

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdSuck::Interrupted() {
	End();
}
