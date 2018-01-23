#include "CmdChangeCamera.h"

CmdChangeCamera::CmdChangeCamera() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::subCameras.get());
}

// Called just before this Command runs the first time
void CmdChangeCamera::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdChangeCamera::Execute() {
	Robot::subCameras->TakeJoystickInputs(Robot::oi->getJoystick0());

}

// Make this return true when this Command no longer needs to run execute()
bool CmdChangeCamera::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdChangeCamera::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdChangeCamera::Interrupted() {

}
