#include "SubIntake.h"
#include "../RobotMap.h"

SubIntake::SubIntake() : Subsystem("ExampleSubsystem") {

}

void SubIntake::InitDefaultCommand() {
	tnxRight = RobotMap::subIntakeTnxRight;
	tnxLeft = RobotMap::subIntakeTnxLeft;
	tnxBottom = RobotMap::subIntakeTnxBottom;

	swtLeftLimit = RobotMap::subIntakeSwtLeftLimit;
	swtRightLimit = RobotMap::subIntakeSwtRightLimit;
}

void SubIntake::Out(){
	tnxRight->Set(1);
	tnxLeft->Set(-1);
	tnxBottom->Set(-1);
}

void SubIntake::In(){
	tnxRight->Set(-1);
	tnxLeft->Set(1);
	tnxBottom->Set(1);
}

void SubIntake::Stop(){
	tnxRight->Set(0);
	tnxLeft->Set(0);
	tnxBottom->Set(0);
}

bool SubIntake::GetSwitches(){
	if (swtLeftLimit->Get() & swtRightLimit->Get() ){
		return true;
	} else {
		return false;
	}
}
