
#include "CmdArmUp.h"

CmdArmUp::CmdArmUp() {
	Requires(Robot::subEncodedArm.get());
}

// Called just before this Command runs the first time
void CmdArmUp::Initialize() {
	Robot::subEncodedArm->PIDEnable();

}

// Called repeatedly when this Command is scheduled to run
void CmdArmUp::Execute() {
	Robot::subEncodedArm->PIDArmTo(0);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdArmUp::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdArmUp::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdArmUp::Interrupted() {
	End();
}
