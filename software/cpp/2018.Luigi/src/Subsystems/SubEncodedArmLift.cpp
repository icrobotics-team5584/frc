#include "SubEncodedArmLift.h"
#include "../RobotMap.h"
#include <iostream>
#include <WPILib.h>
#include <ctre/Phoenix.h>
#include "Constants.h"
#include "Commands/CmdArmDefault.h"

SubEncodedArmLift::SubEncodedArmLift() : Subsystem("ExampleSubsystem") {


	_talon = RobotMap::subEncodedArmLiftSrxMaster;
	_swtTopStop = RobotMap::subEncodedArmLiftSwtTop;
	_swtBottomStop = RobotMap::subEncodedArmLiftSwtBottom;

	targetPositionRotations = 0.0;

}

void SubEncodedArmLift::ArmToGroundPos() {  //Button A

	targetPositionRotations = 0.0;
	_talon->Set(ControlMode::Position, targetPositionRotations);

}

void SubEncodedArmLift::ArmToExchangePos() {  //Button B

	targetPositionRotations = -(1.0 * 4096);
	_talon->Set(ControlMode::Position, targetPositionRotations);

}

void SubEncodedArmLift::ArmToSwitchPos() {  //Button X

	targetPositionRotations = -(2.1 * 4096);
	_talon->Set(ControlMode::Position, targetPositionRotations);

}

void SubEncodedArmLift::ArmToScalePos() {  //Button Y

    targetPositionRotations = -(5.0 * 4096);
	_talon->Set(ControlMode::Position, targetPositionRotations);

}

bool SubEncodedArmLift::GetSwitches() {

	if (_swtTopStop->Get()){
		swtCase = 0;
	} else if (_swtBottomStop->Get()) {
		swtCase = 1;
	} else {
		swtCase = 3;
	}

	if (_swtTopStop->Get() or _swtBottomStop->Get()){
			return true;
		} else {
			return false;
		}
}

int SubEncodedArmLift::GetSwtCase() {
	return swtCase;
}

void SubEncodedArmLift::InitDefaultCommand() {
	SetDefaultCommand(new CmdArmDefault());
}

void SubEncodedArmLift::DefaultStop() {

		targetPositionRotations = (_talon->GetSelectedSensorPosition(0));
		_talon->Set(ControlMode::Position, targetPositionRotations);

}

void SubEncodedArmLift::Stop() {  //for top lim switch
switch (stopCase){
	case 0 :
		targetPositionRotations = (_talon->GetSelectedSensorPosition(0));
		_talon->Set(ControlMode::Position, targetPositionRotations);
	break;
	case 1 :
	break;
}


}

void SubEncodedArmLift::Overide(std::shared_ptr<Joystick> sticky_2) {  //right joystick

	_axis = sticky_2->GetRawAxis(5);

		if (_axis > 0.5) {
			targetPositionRotations = targetPositionRotations + 50;
		} else if (_axis <-0.5){
			targetPositionRotations = targetPositionRotations - 50;
		} else {

		}

		_talon->Set(ControlMode::Position, targetPositionRotations);
}

void SubEncodedArmLift::Reset() { //bottom lim swt reset
switch (stopCase) {
	case 0 :
		_talon->SetSelectedSensorPosition(0,0,10);
		targetPositionRotations = 0;
		_talon->Set(ControlMode::Position, targetPositionRotations);
	break;
	case 1 :
	break;
	}


}

void SubEncodedArmLift::StartBtnReset() { //reset (start button)

	_talon->SetSelectedSensorPosition(0,0,10);
	targetPositionRotations = 0;
	_talon->Set(ControlMode::Position, targetPositionRotations);

}


