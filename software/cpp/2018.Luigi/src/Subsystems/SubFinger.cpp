/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SubFinger.h"
#include "../RobotMap.h"
#include "Commands/CmdFingerDefault.h"
#include "Commands/CmdFingerDown.h"
#include <iostream>

SubFinger::SubFinger() : Subsystem("ExampleSubsystem") {

	_fingerSP = RobotMap::subFingerSP;
	_fingerUpSwt = RobotMap::subFingerSwtFingerUp;

}

//void SubFinger::InitDefaultCommand() {
//	std::cout << "SubFinger::InitDefaultCommand()" << std::endl;
//	SetDefaultCommand(new CmdFingerDefault());
//}

void SubFinger::FingerUp() {
	std::cout << "FingerUp" << std::endl;
	_fingerSP->Set(-0.4);
}


void SubFinger::FingerDown() {
	std::cout << "FingerDown" << std::endl;
	_fingerSP->Set(0.4);
}

void SubFinger::FingerStop() {
	std::cout << "FingerStop" << std::endl;
	_fingerSP->Set(0.0);
	CmdFingerDown * cmdFingerDown;
	cmdFingerDown = new CmdFingerDown;
	cmdFingerDown->Start();
}

void SubFinger::FingerDefaultStop() {
	std::cout << "FingerDefaultStop" << std::endl;
	_fingerSP->Set(0.0);
	_switchCase = 0;
}

bool SubFinger::GetSwitches() {
	std::cout << "GetSwitches OneHere" << std::endl;

	if(_fingerUpSwt->Get() ){
		std::cout << "GetSwitches  TRUE _______" << std::endl;
		return true;
	}
	std::cout << "GetSwitches  FALSE _______" << std::endl;
	return false;

}

int SubFinger::GetSwitchCase() {
	return _switchCase;
}












// Put methods for controlling this subsystem
// here. Call these from Commands.
