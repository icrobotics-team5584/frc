

#include "SubEncodedArm.h"
#include "../RobotMap.h"
#include <SmartDashboard/SmartDashboard.h>
#include "../Commands/CmdArmDefault.h"

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
	SetDefaultCommand(new CmdArmDefault());
}



void SubEncodedArm::Stop() {
	_talon->Set(0.0);
}






