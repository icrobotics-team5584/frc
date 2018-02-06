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
			return true;
		} else {
			return false;
		}
}

void SubEncodedArmLift::InitDefaultCommand() {
	SetDefaultCommand(new CmdArmDefault());
}

void SubEncodedArmLift::DefaultStop() {

		targetPositionRotations = (_talon->GetSelectedSensorPosition(0));
		_talon->Set(ControlMode::Position, targetPositionRotations);

}

void SubEncodedArmLift::Stop() {

		targetPositionRotations = (_talon->GetSelectedSensorPosition(0));
		_talon->Set(ControlMode::Position, (targetPositionRotations +600));

}

void SubEncodedArmLift::Overide(std::shared_ptr<Joystick> sticky_2) {

	_axis = sticky_2->GetRawAxis(5);

		if (_axis > 0.5) {
			targetPositionRotations = targetPositionRotations + 50;
		} else if (_axis <-0.5){
			targetPositionRotations = targetPositionRotations - 50;
		} else {

		}

		_talon->Set(ControlMode::Position, targetPositionRotations);
}

void SubEncodedArmLift::Reset() {

	_talon->SetSelectedSensorPosition(0,0,10);
	targetPositionRotations = 0;
	_talon->Set(ControlMode::Position, targetPositionRotations);

}







