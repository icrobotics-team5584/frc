#include "MotionProfileControl.h"
#include <iostream>

MotionProfileControl::MotionProfileControl(	std::shared_ptr<TalonSRX> LeftTalon,
											std::shared_ptr<TalonSRX> RightTalon,
											const double * LeftMP,
											const double * RightMP,
											const int arrLength)
: _notifier(&MotionProfileControl::PeriodicTask, this)
{
//	std::cout << "MotionProfileControl() MPControl \n";
	_leftMP = (double*)LeftMP;
	_rightMP = (double*)RightMP;
	_arrLength = arrLength;
	_leftTalon = LeftTalon;
	_rightTalon = RightTalon;
	_state = 0;
	_bStart = false;
	_loopTimeout = -1;
	_setValue = SetValueMotionProfile::Disable;
	_notifier.StartPeriodic(0.005);
	_loopCount = 0;

	_leftTalon->ChangeMotionControlFramePeriod(5);
	_rightTalon->ChangeMotionControlFramePeriod(5);
}

void MotionProfileControl::PeriodicTask(){

	if(_leftTalon->GetControlMode() == ControlMode::MotionProfile){

		//Move points from top buffer (on RIO) to bottom buffer (on Talon)
		_leftTalon->ProcessMotionProfileBuffer();
		_rightTalon->ProcessMotionProfileBuffer();

		control();
		_leftTalon->Set(ControlMode::MotionProfile, GetSetValue());
		_rightTalon->Set(ControlMode::MotionProfile, GetSetValue());

	}

}

void MotionProfileControl::reset(){

//	std::cout << "reset() MPControl \n";

	//clean buffer, disable talon, and reset state
	_leftTalon->ClearMotionProfileTrajectories();
	_rightTalon->ClearMotionProfileTrajectories();
	_setValue = SetValueMotionProfile::Disable;
	_state = 0;
	_loopTimeout = -1;
	_bStart = false;
}

void MotionProfileControl::control(){

//	std::cout << "control() MPControl \n";

	//track time to make sure things dont get stuck
	if (_loopTimeout < 0) {
		//do nothing, timeout is disabled
	} else {
		if (_loopTimeout == 0) {
			//Error condition, no progress
//			std::cout << "NO PROGRESS IN MOTION PROFILE LOOP\n";
		} else {
			//Decrement timeout
			--_loopTimeout;
		}
	}

	//Check if we are in MP mode
//	if(_leftTalon->GetControlMode() != ControlMode::MotionProfile){
//		// We are not in MP mode. We are probably using joystick input
//		_state = 0;
//		_loopTimeout = -1;
//	} else {
//		std::cout << "_state:" << _state << "\n";
		switch (_state) {

			case 0: //Start filling
				if (_bStart) {
					std::cout << "case 0, start filling \n";
					//start filling top-buffer with points
					_bStart = false;
					_setValue = SetValueMotionProfile::Disable;
					startFilling(_leftMP, _rightMP, _arrLength );
					std::cout << "changing state 0 to 1 \n";
					_state = 1;
					std::cout << "resetting timeout \n";
					_loopTimeout = kNumLoopsTimeout;
				}
				break;

			case 1: //Start driving
				if (_status.btmBufferCnt > kMinPointsInTalon) {
					std::cout << "case 1, start driving \n";
					//start driving
					_setValue = SetValueMotionProfile::Enable;
					std::cout << "changing state 1 to 2 \n";
					_state = 2;
					_loopTimeout = kNumLoopsTimeout;
				}
				break;

			case 2: //Continue or stop driving
				if (_status.isUnderrun == false) {
//					std::cout << "case 2, running";
					//things going well, reset timeout
					_loopTimeout = kNumLoopsTimeout;
				}
				if (_status.activePointValid && _status.isLast) {
//					std::cout << "case 2, last point";
					//Reached last trajectory point, finish motion profile
					_setValue = SetValueMotionProfile::Hold;
					std::cout << "changing state 2 to 0 \n";
					_state = 0;
					_loopTimeout = -1;
				}
				break;
		}

		// Get the motion profile status every loop
		_leftTalon->GetMotionProfileStatus(_status);
//	}
}

void MotionProfileControl::startFilling(double * LeftMotionProfile, double * RightMotionProfile, int totalCnt){

	std::cout << "startFilling() MPControl\n";
	std::cout << "arrLength :" << totalCnt << "\n";

	//Clear the buffer of previous Motion Profiles
	_leftTalon->ClearMotionProfileTrajectories();
	_rightTalon->ClearMotionProfileTrajectories();

	//Loop through profiles and push each point to talons
	Pos pos;
//	arrL = LeftMotionProfile;
	double arr2[][3]{*RightMotionProfile};

	for (int i = 0; i<totalCnt; ++i) {
		if (i == 0) {pos = first;}
			else if (i == totalCnt) {pos = last;}
			else {pos = mid;}
		std::cout << "arr2[i]: " << arr2[i] << "\n";
//		std::cout << "arrL[i][0]: " << arrL[i][0] << "\n";
//		std::cout << "arrL[i][1]: " << arrL[i][1] << "\n";
//		std::cout << "arrL[i][2]: " << arrL[i][2] << "\n";
//		PushToTalon(LeftMotionProfile[i][0], _leftTalon, pos);
//		PushToTalon(RightMotionProfile[i][0], _rightTalon, pos);
	}

}

void MotionProfileControl::PushToTalon(double MotionProfilePoint[3], std::shared_ptr<TalonSRX> _talon, Pos pos) {

	std::cout << "PushToTalon() MPControl \n";

	//Make a new trajectory point
	TrajectoryPoint point;

	//Fill the top buffer with position and velocity data
	double positionRot = MotionProfilePoint[0];
	double velocityRPM = MotionProfilePoint[1];

	std::cout << "positionRot: " << positionRot << "\n";
	std::cout << "velocityRPM: " << velocityRPM << "\n";

	point.position = positionRot * kSensorUnitsPerRotation;		//Convert revolutions to sensor units
	point.velocity = velocityRPM * kSensorUnitsPerRotation/600;	//Convert RPM to units/100m
	point.timeDur = TrajectoryDuration_10ms;					//Use 10ms for all points

	//Determine first and last points
	point.zeroPos = false;
	point.isLastPoint = false;
	if (pos == first){
		point.zeroPos = true;}
	if (pos == last){
		point.isLastPoint = true;}

	//Push point to Talon
	ctre::phoenix::ErrorCode fredo;
	fredo = _talon->PushMotionProfileTrajectory(point);
	std::cout << "fredo: " << fredo << "\n";
}

void MotionProfileControl::start(){
	std::cout << "start() MPControl \n";

	_bStart = true;
	_leftTalon->Set(ControlMode::MotionProfile, _setValue);
	_rightTalon->Set(ControlMode::MotionProfile, _setValue);
}

void MotionProfileControl::stop(){
	reset();
	_leftTalon->Set(ControlMode::PercentOutput, 0);
	_rightTalon->Set(ControlMode::PercentOutput, 0);
}

SetValueMotionProfile MotionProfileControl::GetSetValue(){
//	std::cout << "GetSetValue() MPControl \n";
	return _setValue;
}
