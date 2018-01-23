#include "CmdAutoRight.h"

CmdAutoRight::CmdAutoRight() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CmdAutoRight::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdAutoRight::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CmdAutoRight::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdAutoRight::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdAutoRight::Interrupted() {

}
