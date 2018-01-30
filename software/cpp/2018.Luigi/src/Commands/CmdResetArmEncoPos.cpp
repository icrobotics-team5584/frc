#include "CmdResetArmEncoPos.h"

CmdResetArmEncoPos::CmdResetArmEncoPos() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::subEncodedArmLift.get());
}

// Called just before this Command runs the first time
void CmdResetArmEncoPos::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdResetArmEncoPos::Execute() {

	Robot::subEncodedArmLift->Reset();

}

// Make this return true when this Command no longer needs to run execute()
bool CmdResetArmEncoPos::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdResetArmEncoPos::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdResetArmEncoPos::Interrupted() {

}
