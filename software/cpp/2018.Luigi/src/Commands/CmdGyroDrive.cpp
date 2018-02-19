#include "CmdGyroDrive.h"

CmdGyroDrive::CmdGyroDrive(double distance, double angle, bool isQuickTurn, bool slow)
:
_distance(distance),
_angle(angle),
_slow(slow),
_isQuickTurn(isQuickTurn)
{
	Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void CmdGyroDrive::Initialize() {
	Robot::subDriveBase->SetPIDIsQuickTurn(_isQuickTurn);
	if (not _isQuickTurn){
		if (_slow){
			Robot::subDriveBase->SetDrivePIDVals(0.55, 0, 0);
			Robot::subDriveBase->GyroDrive(_distance, 0.3);
		} else {
			Robot::subDriveBase->SetDrivePIDVals(0.3, 0, 0);
			Robot::subDriveBase->GyroDrive(_distance, 0.8);
		}
	}
	Robot::subDriveBase->GyroRotate(_angle);
	Robot::subDriveBase->SetDriveMode(SubDriveBase::Autonomous);
}

// Called repeatedly when this Command is scheduled to run
void CmdGyroDrive::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CmdGyroDrive::IsFinished() {
	return Robot::subDriveBase->ReachedSetPoint();
}

// Called once after isFinished returns true
void CmdGyroDrive::End() {
	Robot::subDriveBase->SetDriveMode(SubDriveBase::Manual);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdGyroDrive::Interrupted() {
	End();
}
