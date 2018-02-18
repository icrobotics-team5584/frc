/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SubFinger.h"
#include "../RobotMap.h"
#include "Commands/CmdFingerDefault.h"

SubFinger::SubFinger() : Subsystem("ExampleSubsystem") {

	_fingerSP = RobotMap::subFingerSP;
	_fingerUpSwt = RobotMap::subFingerSwtFingerUp;


}

void SubFinger::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new CmdFingerDefault());
}

void SubFinger::FingerUp() {
	_fingerSP->Set(-0.4);
}


void SubFinger::FingerDown() {
	_fingerSP->Set(0.4);
}

void SubFinger::FingerStop() {
	_fingerSP->Set(0.0);
}

void SubFinger::FingerDefaultStop() {
	_fingerSP->Set(0.0);
	_switchCase = 0;
}

bool SubFinger::GetSwitches() {
	if(_fingerUpSwt->Get()){
		return true;
		_switchCase = 1;
	}else {
		return false;
	}
}

int SubFinger::GetSwitchCase() {
	return _switchCase;
}












// Put methods for controlling this subsystem
// here. Call these from Commands.
