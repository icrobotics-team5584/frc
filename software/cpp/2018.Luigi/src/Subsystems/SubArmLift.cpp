#include "SubArmLift.h"
#include "../RobotMap.h"

SubArmLift::SubArmLift() : Subsystem("ExampleSubsystem") {

}

void SubArmLift::InitDefaultCommand() {
	tnxLeft = RobotMap::subIntakeTnxRight;
	tnxRight = RobotMap::subIntakeTnxLeft;
}

void SubArmLift::Up(){
	tnxRight->Set(1);
	tnxLeft->Set(1);
}

void SubArmLift::Down(){
	tnxRight->Set(1);
	tnxLeft->Set(1);
}

void SubArmLift::Stop(){
	tnxRight->Set(0);
	tnxLeft->Set(0);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
