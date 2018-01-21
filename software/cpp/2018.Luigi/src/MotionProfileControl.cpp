#include "MotionProfileControl.h"
#include "Instrumentation.h"
#include <iostream>

MotionProfileControl::MotionProfileControl(	std::shared_ptr<TalonSRX> LeftTalon,
											std::shared_ptr<TalonSRX> RightTalon,
											std::shared_ptr<MotionProfileData> MP)
: _notifier(&MotionProfileControl::PeriodicTask, this)
{
//	std::cout << "MotionProfileControl() MPControl \n";

	_leftTalon = LeftTalon;
	_rightTalon = RightTalon;
	_mp = MP;
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

	if( (_leftTalon->GetControlMode() == ControlMode::MotionProfile) && (_rightTalon->GetControlMode() == ControlMode::MotionProfile ) ) {

		//Move points from top buffer (on RIO) to bottom buffer (on Talon)
		_leftTalon->ProcessMotionProfileBuffer();
		_rightTalon->ProcessMotionProfileBuffer();

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
			Instrumentation::OnNoProgress();
		} else {
			//Decrement timeout
			--_loopTimeout;
		}
	}

		switch (_state) {

			case 0: //Start filling
				if (_bStart) {
					std::cout << "case 0, start filling \n";
					//start filling top-buffer with points
					_bStart = false;
					_setValue = SetValueMotionProfile::Disable;
					startFilling();
					std::cout << "changing state 0 to 1 \n";
					_state = 1;
					std::cout << "resetting timeout \n";
					_loopTimeout = kNumLoopsTimeout;
				}
				break;

			case 1: //Start driving
				if ( (_statusA.btmBufferCnt > kMinPointsInTalon) && (_statusB.btmBufferCnt > kMinPointsInTalon) ) {
					std::cout << "case 1, start driving \n";
					//start driving
					_setValue = SetValueMotionProfile::Enable;
					std::cout << "changing state 1 to 2 \n";
					_state = 2;
					_loopTimeout = kNumLoopsTimeout;
				}
				break;

			case 2: //Continue or stop driving
				if ( (_statusA.isUnderrun == false) && (_statusB.isUnderrun == false) ) {
					// std::cout << "case 2, running\n";
					//things going well, reset timeout
					_loopTimeout = kNumLoopsTimeout;
				}
				if ( (_statusA.activePointValid && _statusA.isLast) && (_statusB.activePointValid && _statusB.isLast) ){
					std::cout << "case 2, last point\n";
					//Reached last trajectory point, finish motion profile
					_setValue = SetValueMotionProfile::Hold;
					std::cout << "changing state 2 to 0 \n";
					_state = 0;
					_loopTimeout = -1;
				}
				break;
		}

		// Get the motion profile status every loop
		_leftTalon->GetMotionProfileStatus(_statusA);
		_rightTalon->GetMotionProfileStatus(_statusB);

		_headingA = _leftTalon->GetActiveTrajectoryHeading();
		_headingB = _rightTalon->GetActiveTrajectoryHeading();
		_posA = _leftTalon->GetActiveTrajectoryPosition();
		_posB = _rightTalon->GetActiveTrajectoryPosition();
		_velA = _leftTalon->GetActiveTrajectoryVelocity();
		_velB = _rightTalon->GetActiveTrajectoryVelocity();

		// printfs and/or logging ... we really need to process statuses in a better
		// way as they will appear jumbled in the console when we do it like this
		Instrumentation::Process(_statusA, _posA, _velA, _headingA);
		Instrumentation::Process(_statusB, _posB, _velB, _headingB);

}

void MotionProfileControl::startFilling(){

	std::cout << "startFilling() MPControl\n";

	//Clear the buffer of previous Motion Profiles
	_leftTalon->ClearMotionProfileTrajectories();
	_rightTalon->ClearMotionProfileTrajectories();

	//Loop through profiles and push each point to talons
	Pos pos;
    double pointLeft[3];
    double pointRight[3];
    int totalCnt = _mp->GetNumberOfPoints();
    for (int i = 0; i<totalCnt; ++i) {
    	pos = mid;
    	if (i == 0) {
    		pos = first;
    	}
		if (i == totalCnt -1) {
			pos = last;
		}
		pointLeft[0] = _mp->GetPosition(1,i);
		pointLeft[1] = _mp->GetVelocity(1,i);
		pointLeft[2] = _mp->GetDuration(1,i);
		// NOTE: we multiply right side velocity and position by -1 here as the left
		// and right drives are inverted
		pointRight[0] = -1 * _mp->GetPosition(2,i);
		pointRight[1] = -1 * _mp->GetVelocity(2,i);
		pointRight[2] = _mp->GetDuration(2,i);
		// std::cout << "startFilling() MPControl (point:" << i << ")\n";

		if(_statusA.hasUnderrun ){
			/* better log it so we know about it */
			Instrumentation::OnUnderrun();
			/*
			 *
			 * clear the error. This is what seperates "has underrun" from
			 * "is underrun", because the former is cleared by the application.
			 * That way, we never miss logging it.
			 */
			_leftTalon->ClearMotionProfileHasUnderrun(10);
		}
		if(_statusB.hasUnderrun ){
			/* better log it so we know about it */
			Instrumentation::OnUnderrun();
			/*
			 * clear the error. This is what seperates "has underrun" from
			 * "is underrun", because the former is cleared by the application.
			 * That way, we never miss logging it.
			 */
			_rightTalon->ClearMotionProfileHasUnderrun(10);
		}

		PushToTalon(pointLeft, _leftTalon, pos);
		PushToTalon(pointRight, _rightTalon, pos);
	}

}

void MotionProfileControl::PushToTalon(double MotionProfilePoint[3], std::shared_ptr<TalonSRX> _talon, Pos pos) {

	//std::cout << "PushToTalon() MPControl \n";

	//Make a new trajectory point
	TrajectoryPoint point;

	//Set slots
	point.profileSlotSelect0 = 0;
	point.profileSlotSelect1 = 0;

	//Fill the top buffer with position and velocity data
	double positionRot = MotionProfilePoint[0];
	double velocityRPM = MotionProfilePoint[1];
	// double durationMs = MotionProfilePoint[2];

//	std::cout << "  positionRot: " << positionRot << "\n";
//	std::cout << "  velocityRPM: " << velocityRPM << "\n";
//	std::cout << "  durationMs: " << durationMs << "\n";

	point.position = positionRot * kSensorUnitsPerRotation;		//Convert revolutions to sensor units
	point.velocity = velocityRPM * kSensorUnitsPerRotation/600;	//Convert RPM to units/100m
	point.timeDur = TrajectoryDuration_10ms;					//Use 10ms for all points

//	std::cout << "  point.position: " << point.position << "\n";
//	std::cout << "  point.velocity: " << point.velocity << "\n";
//	std::cout << "  point.timeDur: " << point.timeDur << "\n";

	//Determine first and last points
	point.zeroPos = false;
	point.isLastPoint = false;
	if (pos == first){
		point.zeroPos = true;}
	if (pos == last){
		point.isLastPoint = true;}

	//Push point to Talon
	ctre::phoenix::ErrorCode pushpointstatus;
	pushpointstatus = _talon->PushMotionProfileTrajectory(point);
	if( pushpointstatus != 0 ) {
		std::cout << "  push point status: " << pushpointstatus << "\n";
	}

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

void MotionProfileControl::initialise(){
	_rightTalon->Set(ControlMode::MotionProfile, 0);
	_leftTalon->Set(ControlMode::MotionProfile, 0);
	firsttimearound = true;
	execounter = 0;
}

	void MotionProfileControl::execute(){
	control();
	SetValueMotionProfile setOutput = GetSetValue();
	_rightTalon->Set(ControlMode::MotionProfile, setOutput);
	_leftTalon->Set(ControlMode::MotionProfile, setOutput);
	if( firsttimearound )
	{
		start();
		firsttimearound = false;
	}
	execounter++;
}

SetValueMotionProfile MotionProfileControl::GetSetValue(){
//	std::cout << "GetSetValue() MPControl \n";
	return _setValue;
}
