
#include "CmdArmBack.h"

CmdArmBack::CmdArmBack() {
	Requires(Robot::subEncodedArm.get());
}

// Called just before this Command runs the first time
void CmdArmBack::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdArmBack::Execute() {
	Robot::subEncodedArm->PIDArmTo(80);
	Robot::subEncodedArm->PIDEnable();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdArmBack::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdArmBack::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdArmBack::Interrupted() {
	End();
}
