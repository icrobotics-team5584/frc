#include "CmdAutoLeft.h"

CmdAutoLeft::CmdAutoLeft() {
	Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void CmdAutoLeft::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdAutoLeft::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CmdAutoLeft::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdAutoLeft::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdAutoLeft::Interrupted() {

}
