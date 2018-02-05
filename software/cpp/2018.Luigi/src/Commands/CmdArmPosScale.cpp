#include "CmdArmPosScale.h"

CmdArmPosScale::CmdArmPosScale() {

	Requires(Robot::subEncodedArmLift.get());

}

// Called just before this Command runs the first time
void CmdArmPosScale::Initialize() {



}

// Called repeatedly when this Command is scheduled to run
void CmdArmPosScale::Execute() {

	Robot::subEncodedArmLift->ArmToScalePos();

}

// Make this return true when this Command no longer needs to run execute()
bool CmdArmPosScale::IsFinished() {
	if(Robot::subIntake->GetSwitches()){
			return true;
		} else {
				return false;
			}
		}

// Called once after isFinished returns true
void CmdArmPosScale::End() {
	Robot::subEncodedArmLift->CmdDefaStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdArmPosScale::Interrupted() {

}
