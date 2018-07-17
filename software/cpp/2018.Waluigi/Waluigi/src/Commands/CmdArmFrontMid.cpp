
#include "CmdArmFrontMid.h"

CmdArmFrontMid::CmdArmFrontMid() {
	Requires(Robot::subEncodedArm.get());
}

// Called just before this Command runs the first time
void CmdArmFrontMid::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdArmFrontMid::Execute() {
	Robot::subEncodedArm->PIDArmTo(-35);
	Robot::subEncodedArm->PIDEnable();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdArmFrontMid::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdArmFrontMid::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdArmFrontMid::Interrupted() {
	End();
}
