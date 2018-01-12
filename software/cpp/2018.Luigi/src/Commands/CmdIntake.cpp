#include "CmdIntake.h"

CmdIntake::CmdIntake() {
	Requires(Robot::subIntake.get());
}

// Called just before this Command runs the first time
void CmdIntake::Initialize() {
	Robot::subIntake->In();
}

// Called repeatedly when this Command is scheduled to run
void CmdIntake::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CmdIntake::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdIntake::End() {
	Robot::subIntake->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdIntake::Interrupted() {

}
