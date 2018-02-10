#include "SubIntake.h"
#include "../RobotMap.h"

SubIntake::SubIntake() : Subsystem("ExampleSubsystem") {
	tnxRight = RobotMap::subIntakeTnxRight;
	tnxLeft = RobotMap::subIntakeTnxLeft;
	tnxBottom = RobotMap::subIntakeTnxBottom;

	swtLeftLimit = RobotMap::subIntakeSwtLeftLimit;
	swtRightLimit = RobotMap::subIntakeSwtRightLimit;
}

void SubIntake::InitDefaultCommand() {

}

void SubIntake::Out(double speed){
	tnxRight->Set(speed);
	tnxLeft->Set(-speed);
	tnxBottom->Set(-speed);
}

void SubIntake::In(double speed){
	tnxRight->Set(-speed);
	tnxLeft->Set(speed);
	tnxBottom->Set(speed);
}

void SubIntake::Stop(){
	tnxRight->Set(0);
	tnxLeft->Set(0);
	tnxBottom->Set(0);
}

bool SubIntake::GetSwitches(){
	//True if both buttons are pressed
	if (not swtLeftLimit->Get() & not swtRightLimit->Get() ){	//Added nots because switches are normally closed
		return true;
	} else {
		return false;
	}
}
