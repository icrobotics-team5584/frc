#include "CmdArmOveride.h"

CmdArmOveride::CmdArmOveride() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::subEncodedArmLift.get());
}

// Called just before this Command runs the first time
void CmdArmOveride::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdArmOveride::Execute() {
	Robot::subEncodedArmLift->Overide(Robot::oi->getJoystick0());
}

// Make this return true when this Command no longer needs to run execute()
bool CmdArmOveride::IsFinished() {
	if(Robot::subEncodedArmLift->GetSwitches()){
		return true;
	} else {
			return false;
		}
	}

// Called once after isFinished returns true
void CmdArmOveride::End() {
	Robot::subEncodedArmLift->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdArmOveride::Interrupted() {
	End();
}
