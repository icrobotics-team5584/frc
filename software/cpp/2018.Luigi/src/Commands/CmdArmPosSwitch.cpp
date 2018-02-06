#include "CmdArmPosSwitch.h"

CmdArmPosSwitch::CmdArmPosSwitch() {

	Requires(Robot::subEncodedArmLift.get());

}

// Called just before this Command runs the first time
void CmdArmPosSwitch::Initialize() {



}

// Called repeatedly when this Command is scheduled to run
void CmdArmPosSwitch::Execute() {

	Robot::subEncodedArmLift->ArmToSwitchPos();

}

// Make this return true when this Command no longer needs to run execute()
bool CmdArmPosSwitch::IsFinished() {
	if(Robot::subEncodedArmLift->GetSwitches()){
			return true;
		} else {
				return false;
			}
		}

// Called once after isFinished returns true
void CmdArmPosSwitch::End() {
	Robot::subEncodedArmLift->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdArmPosSwitch::Interrupted() {
	End();
}
