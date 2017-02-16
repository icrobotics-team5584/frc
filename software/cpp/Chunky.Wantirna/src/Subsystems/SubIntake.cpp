// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "CANTalon.h"

#include "SubIntake.h"
#include "../RobotMap.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

SubIntake::SubIntake() : Subsystem("SubIntake") {

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    tnxIntakeRollers = RobotMap::subIntakeTnxIntakeRollers;
    tnxIntakeSliders = RobotMap::subIntakeTnxIntakeSliders;
    lswSliderIn = RobotMap::subIntakeLswSliderIn;
    lswSliderOut = RobotMap::subIntakeLswSliderOut;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}

void SubIntake::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void SubIntake::RollerIn() {
	tnxIntakeRollers->Set(1);
}

void SubIntake::RollerOut() {
	tnxIntakeRollers->Set(-1);
}

void SubIntake::RollerOff() {
	tnxIntakeRollers->Set(0);
}

void SubIntake::SliderIn() {
	tnxIntakeSliders->Set(1);
}

void SubIntake::SliderOut() {
	tnxIntakeSliders->Set(-1);
}

void SubIntake::SliderOff() {
	tnxIntakeSliders->Set(0);
}

bool SubIntake::IsSliderOut() {
	return lswSliderOut->Get();
}

bool SubIntake::IsSliderIn() {
	return lswSliderIn->Get();
}
