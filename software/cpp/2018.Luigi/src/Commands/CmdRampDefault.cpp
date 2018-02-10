#include "CmdRampDefault.h"

CmdRampDefault::CmdRampDefault() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::subRamp.get());
}

// Called just before this Command runs the first time
void CmdRampDefault::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdRampDefault::Execute() {

	//Robot::subRamp->TakeJoystickInputs(Robot::oi->getJoystick0());
	sticky_3 = Robot::oi->getJoystick0();

	_POV = sticky_3->GetPOV();

	frc::SmartDashboard::PutNumber("_POV+++++++", _POV);

	if (135 <= _POV && _POV <= 225) {

		frc::SmartDashboard::PutNumber("_POV=========", _POV);

		}

}

// Make this return true when this Command no longer needs to run execute()
bool CmdRampDefault::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdRampDefault::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdRampDefault::Interrupted() {

}
