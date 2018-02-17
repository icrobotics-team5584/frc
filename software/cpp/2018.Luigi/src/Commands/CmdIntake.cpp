#include "CmdIntake.h"
#include <iostream>

CmdIntake::CmdIntake(double timeout, double speed) : _timeout(timeout), _speed(speed) {
	Requires(Robot::subIntake.get());
}

 //Called just before this Command runs the first time
void CmdIntake::Initialize() {
	std::cout << "Running CmdIntake::Initialize()" << std::endl;

	//Start spitting out
	Robot::subIntake->In(_speed);

	//Apply timeout if we are in autonomous mode
	bool autoMode = DriverStation::GetInstance().IsAutonomous();
	if (autoMode){
		SetTimeout(_timeout);
		if (_timeout == 0) {
			std::cout << "WARNING: AUTO INTAKE HAS ZERO TIMEOUT" << std::endl;
		}
	}
}

 //Called repeatedly when this Command is scheduled to run
void CmdIntake::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CmdIntake::IsFinished() {
	if ( (Robot::subIntake->GetSwitches()) or (IsTimedOut()) ) {
		return true;
	} else {
		return false;
	}
}

 //Called once after isFinished returns true
void CmdIntake::End() {
	Robot::subIntake->Stop();
}

 //Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdIntake::Interrupted() {
	End();
}
