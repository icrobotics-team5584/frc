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
	targetPositionRotations = -(1.0 * 4096);
	_talon->Set(ControlMode::Position, targetPositionRotations);


}

void SubEncodedArmLift::ArmToSwitchPos() {  //Button X



	//targetPositionRotations = (_prefs->GetDouble("Switch Position", 0.0))*4096;
	targetPositionRotations = -(2.1 * 4096);
	_talon->Set(ControlMode::Position, targetPositionRotations);

}

void SubEncodedArmLift::ArmToScalePos() {  //Button Y



	//targetPositionRotations = (_prefs->GetDouble("Scale Position", 0.0))*4096;
    targetPositionRotations = -(5.0 * 4096);
	_talon->Set(ControlMode::Position, targetPositionRotations);

}

void SubEncodedArmLift::Periodic() {

//	if (++_loops >= 40) {
//			frc::SmartDashboard::PutNumber("absolutePosition", absolutePosition);
//			frc::SmartDashboard::PutNumber("targetPositionRotations", targetPositionRotations);
//			_loops = 0;
//		}

}

void SubEncodedArmLift::Overide(std::shared_ptr<Joystick> sticky_2) {

	_axis = sticky_2->GetRawAxis(5);

		if (_axis > 0.5) {
			targetPositionRotations = targetPositionRotations - 50;
		} else if (_axis <-0.5){
			targetPositionRotations = targetPositionRotations + 50;
		} else {

		}

		_talon->Set(ControlMode::Position, targetPositionRotations);
}

void SubEncodedArmLift::Reset() {

	_talon->SetSelectedSensorPosition(0,0,10);
	targetPositionRotations = 0;
	_talon->Set(ControlMode::Position, targetPositionRotations);

}




