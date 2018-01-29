#include "SubEncodedArmLift.h"
#include "../RobotMap.h"
#include <iostream>
#include <WPILib.h>
#include <ctre/Phoenix.h>
#include "Constants.h"
#include "Commands/MyJoystickDrive.h"

SubEncodedArmLift::SubEncodedArmLift() : Subsystem("ExampleSubsystem") {



	_talon = RobotMap::subEncodedArmLiftSrxMaster;
	_prefs = Preferences::GetInstance();
	_swtBottomReset = RobotMap::subEncodedArmLiftSwtBottom;

	targetPositionRotations = 0.0;


}

void SubEncodedArmLift::ArmToGroundPos() {  //Button A



	//targetPositionRotations = (_prefs->GetDouble("Ground Position", 0.0))*4096;
	targetPositionRotations = 0.0;
	_talon->Set(ControlMode::Position, targetPositionRotations);


}

void SubEncodedArmLift::ArmToExchangePos() {  //Button B



	//targetPositionRotations = (_prefs->GetDouble("Ground Position", 0.0))*4096;
	targetPositionRotations = (2.5 * 4096);
	_talon->Set(ControlMode::Position, targetPositionRotations);


}

void SubEncodedArmLift::ArmToSwitchPos() {  //Button X



	//targetPositionRotations = (_prefs->GetDouble("Switch Position", 0.0))*4096;
	targetPositionRotations = (3.5 * 4096);
	_talon->Set(ControlMode::Position, targetPositionRotations);

}

void SubEncodedArmLift::ArmToScalePos() {  //Button Y



	//targetPositionRotations = (_prefs->GetDouble("Scale Position", 0.0))*4096;
    targetPositionRotations = (6.0 * 4096);
	_talon->Set(ControlMode::Position, targetPositionRotations);

}

void SubEncodedArmLift::Periodic() {


	absolutePosition = _talon->GetSelectedSensorPosition(0) & 0xFFF;
	if (++_loops >= 40) {
		frc::SmartDashboard::PutNumber("_talon current /start position", absolutePosition);
		_loops = 0;
	}


}


void SubEncodedArmLift::Overide(std::shared_ptr<Joystick> sticky_2) {

	_axis = sticky_2->GetRawAxis(5);
	if (++_axisLoops >= 30) {

		if (_axis > 0.5) {
			-- targetPositionRotations;
		} else if (_axis <-0.5){
			++ targetPositionRotations;
		} else {

		}

		_axisLoops = 0;
	}

	_talon->Set(ControlMode::Position, targetPositionRotations);
	frc::SmartDashboard::PutNumber("AXISUSE", _axis);

}



