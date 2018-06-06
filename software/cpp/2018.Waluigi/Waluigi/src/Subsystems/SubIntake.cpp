/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SubIntake.h"
#include "../RobotMap.h"

//Constructor
SubIntake::SubIntake() : Subsystem("ExampleSubsystem") {

	tnxRight = RobotMap::subIntakeTnxRight;
	tnxLeft = RobotMap::subIntakeTnxLeft;
}

void SubIntake::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

//In
void SubIntake::In(){
	tnxRight->Set(0.5);
	tnxLeft->Set(-0.5);
}

//Out
void SubIntake::Out(){
	tnxRight->Set(-0.5);
	tnxLeft->Set(0.5);
}

void SubIntake::Stop(){
	tnxRight->Set(0);
	tnxLeft->Set(0);
}
