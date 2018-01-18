#include "MotionProfileControl.h"

MotionProfileControl::MotionProfileControl(std::shared_ptr<TalonSRX> LeftTalon, std::shared_ptr<TalonSRX> RightTalon, double LeftMP[][3], double RightMP[][3])
: _notifier(&MotionProfileControl::PeriodicTask, this)
{
	_leftTalon = LeftTalon;
	_rightTalon = RightTalon;
	_leftMP = LeftMP;
	_rightMP = RightMP;
	_state = 0;
	_bStart = false;
	_loopTimeout = -1;
	_setValue = SetValueMotionProfile::Disable;
	_notifier.StartPeriodic(0.005);

	//Setup talons for motion profiling
	for (int i = 0; i<=1; ++i) {
		_talons[i]->Set(ControlMode::MotionProfile, _setValue);
		_talons[i]->ChangeMotionControlFramePeriod(5);
	}
}

void MotionProfileControl::PeriodicTask(){
	//Move points from top buffer (on RIO) to bottom buffer (on Talon)
	_leftTalon->ProcessMotionProfileBuffer();
	_rightTalon->ProcessMotionProfileBuffer();
}

void MotionProfileControl::reset(){
	//clean buffer, disable talon, and reset state
	_leftTalon->ClearMotionProfileTrajectories();
	_rightTalon->ClearMotionProfileTrajectories();
	_setValue = SetValueMotionProfile::Disable;
	_state = 0;
	_loopTimeout = -1;
	_bStart = false;
}

void MotionProfileControl::control(){
	//track time to make sure things dont get stuck
	if (_loopTimeout < 0) {
		//do nothing, timeout is disabled
	} else {
		if (_loopTimeout == 0) {
			//Error condition, no progress
			std::cout << "NO PROGRESS IN MOTION PROFILE LOOP\n";
		} else {
			//Decrement timeout
			--_loopTimeout;
		}
	}

	//Check if we are in MP mode
	if(_leftTalon->GetControlMode() != ControlMode::MotionProfile){
		// We are not in MP mode. We are probably using joystick input
		_state = 0;
		_loopTimeout = -1;
	} else {
		switch (_state) {

			case 0: //Motion Profile not enabled
				if (_bStart) {
					//start filling top-buffer with points
					_bStart = false;
					_setValue = SetValueMotionProfile::Disable;
					startFilling(_leftMP, _rightMP, (int)sizeof(_leftMP)/sizeof(_leftMP[0]) );	//last arg is array size, sizeof() returns size in bytes
					_state = 1;
					_loopTimeout = kNumLoopsTimeout;
				}
				break;

			case 1: //MP has not started and top buffer is full
				if (_status.btmBufferCnt > kMinPointsInTalon) {
					//start driving
					_setValue = SetValueMotionProfile::Enable;
					_state = 2;
					_loopTimeout = kNumLoopsTimeout;
				}
				break;

			case 2: //Motion profile has started
				if (_status.isUnderrun == false) {
					//things going well, reset timeout
					_loopTimeout = kNumLoopsTimeout;
				}
				if (_status.activePointValid && _status.isLast) {
					//Reached last trajectory point, finish motion profile
					_setValue = SetValueMotionProfile::Hold;
					_state = 0;
					_loopTimeout = -1;
				}
				break;
		}

		// Get the motion profile status every loop
		_leftTalon->GetMotionProfileStatus(_status);
	}
}

void MotionProfileControl::startFilling(double LeftMotionProfile[][3], double RightMotionProfile[][3], int totalCnt){

	//Clear the buffer of previous Motion Profiles
	_leftTalon->ClearMotionProfileTrajectories();
	_rightTalon->ClearMotionProfileTrajectories();

	//Loop through profiles and push each point to talons
	Pos pos;
	for (int i = 0; i<totalCnt; ++i) {
		if (i == 0) {pos = first;}
			else if (i == totalCnt) {pos = last;}
			else {pos = mid;}
		PushToTalon(LeftMotionProfile[i], _leftTalon, pos);
		PushToTalon(RightMotionProfile[i], _rightTalon, pos);
	}

}

void MotionProfileControl::PushToTalon(double MotionProfilePoint[3], std::shared_ptr<TalonSRX> _talon, Pos pos) {
	//Make a new trajectory point
	TrajectoryPoint point;

	//Fill the top buffer with position and velocity data
	double positionRot = MotionProfilePoint[0];
	double velocityRPM = MotionProfilePoint[1];

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
	_talon->PushMotionProfileTrajectory(point);
}

void MotionProfileControl::start(){
	_bStart = true;
}

SetValueMotionProfile MotionProfileControl::GetSetValue(){
	return _setValue;
}
