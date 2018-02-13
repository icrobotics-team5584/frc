#include "SubEncodedArmLift.h"
#include "../RobotMap.h"
#include <iostream>
#include <WPILib.h>
#include <ctre/Phoenix.h>
#include "Constants.h"

SubEncodedArmLift::SubEncodedArmLift() : Subsystem("ExampleSubsystem") {


	_talon = RobotMap::subEncodedArmLiftSrxMaster;
	_swtTopStop = RobotMap::subEncodedArmLiftSwtTop;
	_swtTopSecondryStop = RobotMap::subEncodedArmLiftSwtTopSecondary;
	_swtBottomStop = RobotMap::subEncodedArmLiftSwtBottom;

	targetPositionRotations = 0.0;

}

void SubEncodedArmLift::ArmToGroundPos() {  //Button A

	targetPositionRotations = 0.0; //set the targ rotations (total)
	IfBottom(); //check for bottom switch
	IfTop(); //check for top switch
	_talon->Set(ControlMode::Position, targetPositionRotations); //start the background loop that goes to targtPo...
	MovementCheck(); //check for moved of switch to reset stopCase back to 0 ready for another switch press

}

void SubEncodedArmLift::ArmToExchangePos() {  //Button B

	targetPositionRotations = -(0.39 * 4096);
	IfBottom();
	IfTop();
	_talon->Set(ControlMode::Position, targetPositionRotations);
	MovementCheck();

}

void SubEncodedArmLift::ArmToSwitchPos() {  //Button X

	targetPositionRotations = -(2.1 * 4096);
	IfBottom();
	IfTop();
	_talon->Set(ControlMode::Position, targetPositionRotations);
	MovementCheck();

}

void SubEncodedArmLift::ArmToScalePos() {  //Button Y

    targetPositionRotations = -(5.5 * 4096);
    IfBottom();
    IfTop();
	_talon->Set(ControlMode::Position, targetPositionRotations);
	MovementCheck();

}

void SubEncodedArmLift::Overide(std::shared_ptr<Joystick> sticky_2) {  //right joystick button press

	_axis5 = sticky_2->GetRawAxis(5); //up down control axis
	_axis3 = sticky_2->GetRawAxis(3); //right trigger overide boost

	_btn7 = sticky_2->GetRawButton(7); //one when pressed
	if (_btn7 >= 1.0) {
		stopCase = 1;
	} else {
		stopCase = 0;
	}

	if (_axis3 > 0.5) { //checks if axes3 (right trig held) if change case for overideSpeed
		overideCase = 1;
	} else {
		overideCase = 0;
	}

	switch (overideCase) { //change overideSpeed based on overideCase
	case 0:
		overideSpeed = 50;
	break;
	case 1:
		overideSpeed = 150;
	break;
	}

	if (_axis5 > 0.5) { //down
		targetPositionRotations = targetPositionRotations + overideSpeed;
		IfBottom();
		IfTop();
	} else if (_axis5 <-0.5){ //up
		targetPositionRotations = targetPositionRotations - overideSpeed;
		IfBottom();
		IfTop();
	} else {
	}

		_talon->Set(ControlMode::Position, targetPositionRotations);
		MovementCheck();

}


bool SubEncodedArmLift::GetSwitches() { //run evry ~20ms checks the switch states

	//frc::SmartDashboard::PutNumber("Where It Is Now ??????????", targetPositionRotations); //this is for checking heights

	if (_swtTopStop->Get() or _swtTopSecondryStop->Get()){ //this if statement is so it knows what funtion to call in end
		swtCase = 0;
	} else if (_swtBottomStop->Get()) {
		swtCase = 1;
	} else {
		swtCase = 3;
	}

	switch (stopCase) {//this is determs weather or not we want to ignore the switch
	default:
	if (_swtTopStop->Get() or _swtBottomStop->Get() or _swtTopSecondryStop->Get()){
			return true;
		} else {
			return false;
		}
	break;
	case 1 :
		return false ;
	break;
	}
}

int SubEncodedArmLift::GetSwtCase() { //this is for commands End()s so they can get swtCase
	return swtCase;
}

void SubEncodedArmLift::Stop() {  //for top lim switch

		targetPositionRotations = (_talon->GetSelectedSensorPosition(0));
		_talon->Set(ControlMode::Position, targetPositionRotations);

}

void SubEncodedArmLift::Reset() { //for bottom lim swt reset

		_talon->SetSelectedSensorPosition(0,0,10);
		targetPositionRotations = 0;
		_talon->Set(ControlMode::Position, targetPositionRotations);

}

void SubEncodedArmLift::StartBtnReset() { //reset (start button) xbox 360 controler

	_talon->SetSelectedSensorPosition(0,0,10);
	targetPositionRotations = 0;
	_talon->Set(ControlMode::Position, targetPositionRotations);

}


int SubEncodedArmLift::GetCurrentPosition() {

	//Return current position of the lift encoder in sensor units
	return _talon->GetSelectedSensorPosition(0);

}

int SubEncodedArmLift::GetTargetPosition() {

	//Return target position of the lift encoder in sensor units
	return (targetPositionRotations / 4096);

}

void SubEncodedArmLift::IfBottom() { //can it move off bottom switch???

	if (_swtBottomStop->Get()) {
		if (targetPositionRotations < (_talon->GetSelectedSensorPosition(0))) {
			stopCase = 1;
		}
	}

}

void SubEncodedArmLift::IfTop() { //can it move off TOP switch???

	if (_swtTopStop->Get() or _swtTopSecondryStop->Get()) {
			if (targetPositionRotations > (_talon->GetSelectedSensorPosition(0))) {
				stopCase = 1;
			}
		}

}

void SubEncodedArmLift::MovementCheck() {


 //check for switch not prssed

	if(not _swtTopStop->Get() && (not (_swtBottomStop->Get() or _swtTopSecondryStop->Get())) ){
		stopCase = 0;
	}

}


