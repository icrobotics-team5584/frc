#include "CmdPnuematicOutputOut.h"
#include "Robot.h"
#include "SubPnuematicOutput.h"

CmdPnuematicOutputOut::CmdPnuematicOutputOut() {
	Requires(Robot::subPnuematicOutput.get());
}

// Called just before this Command runs the first time
void CmdPnuematicOutputOut::Initialize() {
	Robot::subPnuematicOutput->Out();
}

// Called repeatedly when this Command is scheduled to run
void CmdPnuematicOutputOut::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CmdPnuematicOutputOut::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdPnuematicOutputOut::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdPnuematicOutputOut::Interrupted() {

}
