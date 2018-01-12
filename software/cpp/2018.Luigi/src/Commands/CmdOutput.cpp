#include "CmdOutput.h"

CmdOutput::CmdOutput() {
	Requires(Robot::subIntake.get());
}

// Called just before this Command runs the first time
void CmdOutput::Initialize() {
	Robot::subIntake->Out();
}

// Called repeatedly when this Command is scheduled to run
void CmdOutput::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CmdOutput::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdOutput::End() {
	Robot::subIntake->In();
}

// Called when another command which requires one or more of the same subsystems is scheduled to run
void CmdOutput::Interrupted() {
	End();
}
