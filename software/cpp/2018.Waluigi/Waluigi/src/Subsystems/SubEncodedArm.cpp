

#include "SubEncodedArm.h"
#include "../RobotMap.h"
#include <SmartDashboard/SmartDashboard.h>

SubEncodedArm::SubEncodedArm() : Subsystem("ExampleSubsystem") {

	_talon = RobotMap::subEncodedArmTnx;
	_potMain = RobotMap::subEncodedArmPot;

}

void SubEncodedArm::Periodic() {

	lc++;
	if( lc > 10){
		SmartDashboard::PutNumber("POT Value", _potMain->GetValue());
		SmartDashboard::PutNumber("POT Voltage", _potMain->GetVoltage());
		SmartDashboard::PutNumber("POT Value Average", _potMain->GetAverageValue());
		SmartDashboard::PutNumber("POT Voltage Average", _potMain->GetAverageVoltage());
		lc = 0;
	}


}

void SubEncodedArm::InitDefaultCommand() {

}


