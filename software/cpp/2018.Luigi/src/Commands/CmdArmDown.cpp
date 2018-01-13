#include "CmdArmDown.h"

CmdArmDown::CmdArmDown() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::subArmLift.get());
}

// Called just before this Command runs the first time
void CmdArmDown::Initialize() {
	Robot::subArmLift->Down();

}

// Called repeatedly when this Command is scheduled to run
void CmdArmDown::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CmdArmDown::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdArmDown::End() {
	Robot::subArmLift->Stop();

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdArmDown::Interrupted() {

}
