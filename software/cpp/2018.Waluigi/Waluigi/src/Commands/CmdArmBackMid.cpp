
#include "CmdArmBackMid.h"

CmdArmBackMid::CmdArmBackMid() {
	Requires(Robot::subEncodedArm.get());
}

// Called just before this Command runs the first time
void CmdArmBackMid::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdArmBackMid::Execute() {
	Robot::subEncodedArm->PIDArmTo(45);
	Robot::subEncodedArm->PIDEnable();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdArmBackMid::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdArmBackMid::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdArmBackMid::Interrupted() {
	End();
}
