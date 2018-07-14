

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

void SubEncodedArm::ArmJoyMove(std::shared_ptr<frc::Joystick> controller) {
	_axis5 = controller->GetRawAxis(5); //up down control axis
	double speed = 0.0;
	speed = _axis5;
	_talon->Set(speed);  //Probably will need some extra stuff in here for better control / movement

}

void SubEncodedArm::Stop() {	//Used by the default command
	_talon->Set(0.0);
}






