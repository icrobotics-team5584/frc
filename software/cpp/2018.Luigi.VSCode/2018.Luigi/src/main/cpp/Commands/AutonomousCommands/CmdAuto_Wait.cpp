#include "CmdAuto_Wait.h"
#include <iostream>

CmdAuto_Wait::CmdAuto_Wait(double timeout) : _timeout(timeout) {

}

// Called just before this Command runs the first time
void CmdAuto_Wait::Initialize() {
	std::cout << "Starting delayed lift" << std::endl;
	SetTimeout(_timeout);
}

// Called repeatedly when this Command is scheduled to run
void CmdAuto_Wait::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CmdAuto_Wait::IsFinished() {
	return IsTimedOut();
}

// Called once after isFinished returns true
void CmdAuto_Wait::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdAuto_Wait::Interrupted() {
	End();
}
