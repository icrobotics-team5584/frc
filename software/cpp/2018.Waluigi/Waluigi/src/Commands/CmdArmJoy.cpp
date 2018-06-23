

#include "CmdArmJoy.h"

CmdArmJoy::CmdArmJoy() {
	Requires(Robot::subEncodedArm.get());
}

// Called just before this Command runs the first time
void CmdArmJoy::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdArmJoy::Execute() {
	Robot::subEncodedArm->ArmJoyMove(Robot::oi->getJoystick());
}

// Make this return true when this Command no longer needs to run execute()
bool CmdArmJoy::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdArmJoy::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdArmJoy::Interrupted() {

}
