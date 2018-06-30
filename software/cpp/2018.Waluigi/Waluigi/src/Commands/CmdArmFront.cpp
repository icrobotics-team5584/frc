

#include "CmdArmFront.h"

CmdArmFront::CmdArmFront() {
	Requires(Robot::subEncodedArm.get());
}

// Called just before this Command runs the first time
void CmdArmFront::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdArmFront::Execute() {
	Robot::subEncodedArm->PIDArmTo(-80);
	Robot::subEncodedArm->PIDEnable();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdArmFront::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdArmFront::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdArmFront::Interrupted() {
	End();
}
