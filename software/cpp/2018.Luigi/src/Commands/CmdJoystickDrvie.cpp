#include "CmdJoystickDrvie.h"

CmdJoystickDrvie::CmdJoystickDrvie() {
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void CmdJoystickDrvie::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdJoystickDrvie::Execute() {
	Robot::subDriveBase->TakeJoystickInputs(Robot::oi->GetJoystick1() );


}

// Make this return true when this Command no longer needs to run execute()
bool CmdJoystickDrvie::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdJoystickDrvie::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdJoystickDrvie::Interrupted() {

}
