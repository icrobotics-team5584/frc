#include "CmdArmDefault.h"

CmdArmDefault::CmdArmDefault() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::subEncodedArmLift.get());
}

// Called just before this Command runs the first time
void CmdArmDefault::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdArmDefault::Execute() {
	Robot::subEncodedArmLift->DefaultStop();
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
