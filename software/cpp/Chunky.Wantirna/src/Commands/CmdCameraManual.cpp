#include "CmdCameraManual.h"

CmdCameraManual::CmdCameraManual() {
	Requires(Robot::subCamera.get());
}

// Called just before this Command runs the first time
void CmdCameraManual::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdCameraManual::Execute() {
	std::shared_ptr<Joystick> stick = Robot::oi->getJoystick1();
	Robot::subCamera->Pan(stick->GetRawAxis(2));
	Robot::subCamera->Tilt(stick->GetRawAxis(5));
	Robot::subCamera->PublishValues();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdCameraManual::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdCameraManual::End() {
	Robot::subCamera->Stop();

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdCameraManual::Interrupted() {

}
