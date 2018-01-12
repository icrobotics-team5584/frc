#include "CmdAutoBackward.h"

CmdAutoBackward::CmdAutoBackward() {
	Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void CmdAutoBackward::Initialize() {
	SetTimeout(2);
}

// Called repeatedly when this Command is scheduled to run
void CmdAutoBackward::Execute() {
	Robot::subDriveBase->AutoDrive(-0.5, 0);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdAutoBackward::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdAutoBackward::End() {
	Robot::subDriveBase->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdAutoBackward::Interrupted() {
	End();
}
