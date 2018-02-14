#include "CmdGyroTurn.h"
#include "Subsystems/SubDriveBase.h"

CmdGyroTurn::CmdGyroTurn(double angle, bool relative)
:
_angle(angle),
_relative(relative),
relativeAngle(Robot::subDriveBase->GetAngle() + _angle)
{
	Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void CmdGyroTurn::Initialize() {
	Robot::subDriveBase->SetDriveMode(SubDriveBase::Gyroscope);

	if (_relative){
		//turn as if current direction is zero
		relativeAngle = Robot::subDriveBase->GetAngle() + _angle;
		Robot::subDriveBase->Rotate(_angle);
	} else {
		//turn as if the robot's starting angle is zero
		Robot::subDriveBase->Rotate(_angle);
	}
}

// Called repeatedly when this Command is scheduled to run
void CmdGyroTurn::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CmdGyroTurn::IsFinished() {
	return Robot::subDriveBase->ReachedTarget();
}

// Called once after isFinished returns true
void CmdGyroTurn::End() {
	Robot::subDriveBase->Stop();
	Robot::subDriveBase->SetDriveMode(SubDriveBase::Manual);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdGyroTurn::Interrupted() {
	End();
}
