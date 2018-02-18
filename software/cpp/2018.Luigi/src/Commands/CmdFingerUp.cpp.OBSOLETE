/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CmdFingerUp.h"

CmdFingerUp::CmdFingerUp() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CmdFingerUp::Initialize() {

	std::cout << "CmdFingerUp::Initialize()  " << std::endl;
	Robot::subFinger->FingerUp();

}

// Called repeatedly when this Command is scheduled to run
void CmdFingerUp::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CmdFingerUp::IsFinished() {

	std::cout << "CmdFingerUp::IsFinished()  " << std::endl;
	if(Robot::subFinger->GetSwitches()){
		std::cout << "CmdFingerUp::IsFinished() TRUEEEE  " << std::endl;
		return true;
	}else {
		return false;
	}

}

// Called once after isFinished returns true
void CmdFingerUp::End() {
	std::cout << "CmdFingerUp::End() " << std::endl;
	Robot::subFinger->FingerStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdFingerUp::Interrupted() {

}
