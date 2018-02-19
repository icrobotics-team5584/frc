#include "SubIntake.h"
#include "../RobotMap.h"

SubIntake::SubIntake() : Subsystem("ExampleSubsystem") {
	tnxRight = RobotMap::subIntakeTnxRight;
	tnxLeft = RobotMap::subIntakeTnxLeft;
	spFinger = RobotMap::subIntakeSpFinger;
	swtFingerLimit = RobotMap::subIntakeSwtFingerUp;
	swtLeftLimit = RobotMap::subIntakeSwtLeftLimit;
	swtRightLimit = RobotMap::subIntakeSwtRightLimit;
	fingerDesiredPositionUp = false;
	fingerTicks = fingerTicksToMove;
}

void SubIntake::InitDefaultCommand() {
}

void SubIntake::Periodic() {
	if( fingerDesiredPositionUp ) {
		if( swtFingerLimit->Get() ) {
			//std::cout << "SubIntake::Periodic: Switch Desired Position UP and switch TRUE" << std::endl;
			// finger is up and in the correct position so stop the motor
			spFinger->Set(0.0);
		} else {
			//std::cout << "SubIntake::Periodic: Switch Desired Position UP and switch FALSE" << std::endl;
			// finger is not in the up position so set it off in that direction
			spFinger->Set(-1.0);
		}
	}

	if( ! fingerDesiredPositionUp ) {
		if( swtFingerLimit->Get() ) {
			//std::cout << "SubIntake::Periodic: Switch Desired Position DOWN and switch TRUE" << std::endl;
			// we need to launch the finger down movement
			fingerTicks = 0;
			spFinger->Set(1.0);

		} else {
			//std::cout << "SubIntake::Periodic: Switch Desired Position DOWN and switch FALSE" << std::endl;
			// the movement is in progress or the finger is already down, lets check if we are there yet ...
			if( fingerTicks >= fingerTicksToMove ){
				// we have moved far enough so lets hold up here ...
				spFinger->Set(0.0);
			} else {
			fingerTicks++;
			}
		}
	}

}

void SubIntake::Out(double speed){
	tnxRight->Set(speed);
	tnxLeft->Set(-speed);
	fingerDesiredPositionUp = true;
}

void SubIntake::In(double speed){
	tnxRight->Set(-speed);
	tnxLeft->Set(speed);
	fingerDesiredPositionUp = true;
}

void SubIntake::Stop(){
	tnxRight->Set(0);
	tnxLeft->Set(0);
	fingerDesiredPositionUp = false;
}

bool SubIntake::GetSwitches(){
	//True if both buttons are pressed
	if (not swtLeftLimit->Get() & not swtRightLimit->Get() ){	//Added nots because switches are normally closed
		return true;
	} else {
		return false;
	}
}
