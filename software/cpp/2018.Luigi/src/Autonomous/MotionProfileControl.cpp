#include "MotionProfileControl.h"
#include "Instrumentation.h"
#include <iostream>

MotionProfileControl::MotionProfileControl(	std::shared_ptr<TalonSRX> LeftTalon,
											std::shared_ptr<TalonSRX> RightTalon,
											std::string profile,
											int profileTimeout)
: _notifier(&MotionProfileControl::PeriodicTask, this), _profileTimeout(profileTimeout)
{

	//Assign variables
	_leftTalon = LeftTalon;
	_rightTalon = RightTalon;
	_profile = profile;
	_state = 0;
	_bStart = false;
	_loopTimeout = -1;
	_setValue = SetValueMotionProfile::Disable;
	_notifier.StartPeriodic(0.005);
	_loopCount = 0;
	_pointsprocessed = 0;

	_leftTalon->ChangeMotionControlFramePeriod(5);
	_rightTalon->ChangeMotionControlFramePeriod(5);

	isRunning = true;
}

void MotionProfileControl::PeriodicTask(){
	//Make sure we are in Motion Profile mode
	if( (_leftTalon->GetControlMode() == ControlMode::MotionProfile) && (_rightTalon->GetControlMode() == ControlMode::MotionProfile ) ) {
		//Move points from top buffer (on RIO) to bottom buffer (on Talon)
		_leftTalon->ProcessMotionProfileBuffer();
		_rightTalon->ProcessMotionProfileBuffer();
	}
	execounter++;
	if ((execounter >= 200) and (_profileTimeout > -1)){
		_profileTimeout--;
		execounter = 0;
	}

}

void MotionProfileControl::reset(){

	std::cout << "MotionProfileControl: reset" << std::endl;

	//clean buffer
	_leftTalon->ClearMotionProfileTrajectories();
	_rightTalon->ClearMotionProfileTrajectories();

	//disable talon, and reset state
	_setValue = SetValueMotionProfile::Disable;
	_state = 0;
	_loopTimeout = -1;
	_bStart = false;

	//Reset Sensor positions to zero for future profiles
	_leftTalon->SetSelectedSensorPosition(0, 0, 10);
	_rightTalon->SetSelectedSensorPosition(0, 0, 10);
}

void MotionProfileControl::control(){
	//track time to make sure things don't get stuck
	if (_loopTimeout < 0) {
		//do nothing, timeout is disabled
	} else {
		if (_loopTimeout == 0) {
			//Error condition, no progress
			Instrumentation::OnNoProgress();
		} else {
			//Decrement timeout
			--_loopTimeout;
		}
	}

	switch (_state) {

		case 0: //Start filling top-buffer with points
			if (_bStart) {
				_bStart = false;
				_setValue = SetValueMotionProfile::Disable;
				// try sending some points ...
				streamToTopBuffer( true );
				_state = 1;
				_loopTimeout = kNumLoopsTimeout;
			}
			break;

		case 1: //Start driving
			if ( (_statusA.btmBufferCnt > kMinPointsInTalon) && (_statusB.btmBufferCnt > kMinPointsInTalon) ) {
				_setValue = SetValueMotionProfile::Enable;
				// try sending some points ...
				streamToTopBuffer( false );
				_state = 2;
				_loopTimeout = kNumLoopsTimeout;
			}
			break;

		case 2: //Continue or stop driving
			if ( (_statusA.isUnderrun == false) && (_statusB.isUnderrun == false) ) {
				//things going well, reset timeout
				_loopTimeout = kNumLoopsTimeout;
			} else {
				//Talons don't have enough points, log an underrun
			}

			// try sending some points ...
			streamToTopBuffer( false );

			//Stop if profile timed out
			if (_profileTimeout <= 0){
				std::cout << "Profile timed out" << std::endl;
				stop();
			}

			//Uncomment these to find out why the MP isn't ending
//			std::cout << "_statusA.activePointValid: " << _statusA.activePointValid << std::endl;
//			std::cout << "_statusA.isLast: " << _statusA.isLast << std::endl;
//			std::cout << "_statusB.activePointValid: " << _statusB.activePointValid << std::endl;
//			std::cout << "_statusB.isLast: " << _statusB.isLast << std::endl;

			if ( (_statusA.activePointValid && _statusA.isLast) || (_statusB.activePointValid && _statusB.isLast) ){
				//Reached last trajectory point, finish motion profile
				_setValue = SetValueMotionProfile::Hold;
				stop();
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
//		Instrumentation::Process(_statusA, _posA, _velA, _headingA);
//		Instrumentation::Process(_statusB, _posB, _velB, _headingB);

}

void MotionProfileControl::streamToTopBuffer( bool firstpass ){

	if( firstpass ) {

		//Clear the buffer of previous Motion Profiles
		_leftTalon->ClearMotionProfileTrajectories();
		_rightTalon->ClearMotionProfileTrajectories();

		//set the base trajectory period to zero, use the individual trajectory periods in PushToTalon(...)
		_leftTalon->ConfigMotionProfileTrajectoryPeriod(0, 10);
		_rightTalon->ConfigMotionProfileTrajectoryPeriod(0, 10);
	}

	//Check if talons have run out of points
	if(_statusA.hasUnderrun){
		// Log it in the console
		Instrumentation::OnUnderrun();
		 /*
		  * Clear the error. This is what seperates "has underrun" from
		  * "is underrun", because the former is cleared by the application.
		  * That way, we never miss logging it.
		  */
		_leftTalon->ClearMotionProfileHasUnderrun(10);
	}
	if(_statusB.hasUnderrun ){
		// Log it in the console
		Instrumentation::OnUnderrun();
		/*
		 * Clear the error. This is what seperates "has underrun" from
		 * "is underrun", because the former is cleared by the application.
		 * That way, we never miss logging it.
		 */
		_rightTalon->ClearMotionProfileHasUnderrun(10);
	}

	// decide how many blocks to process
	int _topBufferRemA = _statusA.topBufferRem;
	int _topBufferRemB = _statusB.topBufferRem;
	int _minTopBufferRem = ( _topBufferRemA < _topBufferRemB ) ? _topBufferRemA : _topBufferRemB;
	int _blocks = 0;
	if( firstpass ) {
		// process as many blocks as possible (zero or more)
		_blocks = trunc( _minTopBufferRem / kBlockSize );
	}
	if( ! firstpass ) {
		// process zero or one blocks
		_blocks = ( _minTopBufferRem > kBlockSize ) ? 1 : 0;
	}

//	std::cout << "INFO: processing " << _blocks << " blocks" << std::endl;

	// no process the zero or more blocks
	while( _blocks > 0 ) {
		int mpsize = _mpData.GetNumberOfPoints();
		int start = _pointsprocessed;
//		std::cout << "INFO: points processed (before): " << _pointsprocessed << "/" << mpsize << std::endl;
		int finish;
		int remaining = mpsize - _pointsprocessed;
		if( remaining > kBlockSize ) {
			finish = _pointsprocessed + kBlockSize;
		} else {
			finish = _pointsprocessed + remaining;
		}
		for (int i = start; i<finish; i++){
			PushToTalon(_mpData.GetPoint(0, i), _leftTalon, 0);
			PushToTalon(_mpData.GetPoint(1, i), _rightTalon, 1);
		}
		_pointsprocessed = finish;
//		std::cout << "INFO: points processed (after): " << _pointsprocessed << "/" << mpsize << std::endl;
		_blocks--;
	}
}

void MotionProfileControl::PushToTalon(TrajectoryPoint point, std::shared_ptr<TalonSRX> _talon, int side) {
	//Uncomment these to find out if the top buffer is filling up
//	std::cout << "Left top-buffer count: " << _leftTalon->GetMotionProfileTopLevelBufferCount() << " out of " << kTopBufferSize << std::endl;
//	std::cout << "Right top-buffer count: " << _rightTalon->GetMotionProfileTopLevelBufferCount() << " out of " << kTopBufferSize << std::endl;

	//negate right side because motor is inverted
	if (side == 1) {
		point.position *= -1;
		point.velocity *= -1;
	}

	//Convert pos and vel to sensor units
	point.position = point.position * kSensorUnitsPerRotation;
	point.velocity = point.velocity * kSensorUnitsPerRotation/600;

	//Push point to Talon
	ctre::phoenix::ErrorCode pushpointstatus;
	pushpointstatus = _talon->PushMotionProfileTrajectory(point);
	if( pushpointstatus != 0 ) {
		std::cout << "  push point status: " << pushpointstatus << "\n";
	}
}

void MotionProfileControl::start(){
	//signal to control() to start filling
	_bStart = true;

	//Put Talons in Motion Profile Mode
	_leftTalon->Set(ControlMode::MotionProfile, _setValue);
	_rightTalon->Set(ControlMode::MotionProfile, _setValue);
}

void MotionProfileControl::stop(){
	std::cout << "MotionProfileControl: stop" << std::endl;
	//Reset variables and objects (controllers, sensors, etc)
	reset();
	isRunning = false;

	//Put talons back in manual mode
	_leftTalon->Set(ControlMode::PercentOutput, 0);
	_rightTalon->Set(ControlMode::PercentOutput, 0);
}

void MotionProfileControl::load(){
	std::cout << "MotionProfileControl: load" << std::endl;
	_mpData.ReadMotionProfile(_profile);
}

void MotionProfileControl::initialise(){

	std::cout << "MotionProfileControl: initialise" << std::endl;
	//Put Talons in MP mode
	_rightTalon->Set(ControlMode::MotionProfile, 0);
	_leftTalon->Set(ControlMode::MotionProfile, 0);

	//Setup start vars (used in execute())
	firsttimearound = true;
	execounter = 0;
	isRunning = true;
}

void MotionProfileControl::execute(){
	//Determine what to do based on state
	control();
	SmartDashboard::PutNumber("_loopTimeout", _loopTimeout);

	//Set talons to take motion profile points
	SetValueMotionProfile setOutput = GetSetValue();
	_rightTalon->Set(ControlMode::MotionProfile, setOutput);
	_leftTalon->Set(ControlMode::MotionProfile, setOutput);

	//Start filling
	if( firsttimearound ) {
		start();
		firsttimearound = false;
	}
}

SetValueMotionProfile MotionProfileControl::GetSetValue(){
	//Return Disable, Enable, or Hold
	return _setValue;
}

bool MotionProfileControl::IsRunning(){
	return isRunning;
}
