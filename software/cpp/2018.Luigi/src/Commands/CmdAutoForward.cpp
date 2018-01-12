#include "CmdAutoForward.h"

CmdAutoForward::CmdAutoForward() {
	Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void CmdAutoForward::Initialize() {
	SetTimeout(2);
}

// Called repeatedly when this Command is scheduled to run
void CmdAutoForward::Execute() {
	Robot::subDriveBase->AutoDrive(0.5, 0);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdAutoForward::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdAutoForward::End() {
	Robot::subDriveBase->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdAutoForward::Interrupted() {
	End();
}
