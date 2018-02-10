#include "CmdAuto_BasicDrive.h"

CmdAuto_BasicDrive::CmdAuto_BasicDrive(double speed, double rotation) : _speed(speed), _rotation(rotation) {
	Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void CmdAuto_BasicDrive::Initialize() {
	Robot::subDriveBase->AutoDrive(_speed, _rotation);
}

// Called repeatedly when this Command is scheduled to run
void CmdAuto_BasicDrive::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CmdAuto_BasicDrive::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdAuto_BasicDrive::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdAuto_BasicDrive::Interrupted() {

}
