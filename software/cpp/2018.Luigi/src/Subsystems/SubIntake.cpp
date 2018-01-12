#include "SubIntake.h"
#include "../RobotMap.h"

SubIntake::SubIntake() : Subsystem("ExampleSubsystem") {

}

void SubIntake::InitDefaultCommand() {
	tnxRight = RobotMap::subIntakeTnxRight;
	tnxLeft = RobotMap::subIntakeTnxLeft;
}

void SubIntake::Out(){
	tnxRight->Set(1);
	tnxLeft->Set(-1);
}

void SubIntake::In(){
	tnxRight->Set(-1);
	tnxLeft->Set(1);
}

void SubIntake::Stop(){
	tnxRight->Set(0);
	tnxLeft->Set(0);
}
