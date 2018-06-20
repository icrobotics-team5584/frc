

#include "CmdArmDefault.h"

CmdArmDefault::CmdArmDefault() {
	Requires(Robot::subEncodedArm.get());
}

// Called just before this Command runs the first time
void CmdArmDefault::Initialize() {
	Robot::subEncodedArm->Stop();
}

// Called repeatedly when this Command is scheduled to run
void CmdArmDefault::Execute() {
	Robot::subEncodedArm->Stop();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdArmDefault::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdArmDefault::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdArmDefault::Interrupted() {

}
