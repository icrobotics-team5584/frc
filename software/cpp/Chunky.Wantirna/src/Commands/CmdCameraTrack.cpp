#include "CmdCameraTrack.h"
#include "WPILib.h"
#include "OI.h"


CmdCameraTrack::CmdCameraTrack() {
	Requires(Robot::subCamera.get());

}

// Called just before this Command runs the first time
void CmdCameraTrack::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdCameraTrack::Execute() {
	//Move camera according to image processing values
	Robot::subCamera->Pan(Robot::subDriveBase->GetPegX());
	Robot::subCamera->Tilt(Robot::subDriveBase->GetPegY());
}

// Make this return true when this Command no longer needs to run execute()
bool CmdCameraTrack::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdCameraTrack::End() {
	Robot::subCamera->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdCameraTrack::Interrupted() {

}
