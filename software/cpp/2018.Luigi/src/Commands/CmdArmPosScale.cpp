#include "CmdArmPosScale.h"
#include <iostream>

CmdArmPosScale::CmdArmPosScale() {

	Requires(Robot::subEncodedArmLift.get());

}

// Called just before this Command runs the first time
void CmdArmPosScale::Initialize() {

	std::cout << "Moving arm to scale" << std::endl;

}

// Called repeatedly when this Command is scheduled to run
void CmdArmPosScale::Execute() {

	Robot::subEncodedArmLift->ArmToScalePos();

}

// Make this return true when this Command no longer needs to run execute()
bool CmdArmPosScale::IsFinished() {
	if (Robot::subEncodedArmLift->GetSwitches()){
		//Stop command if hit limit switches
		return true;
	}

	if (Robot::subEncodedArmLift->GetCurrentPosition() == Robot::subEncodedArmLift->GetTargetPosition()){
		//Stop command if target position is reached
		return true;
	}

	return false;
}

// Called once after isFinished returns true
void CmdArmPosScale::End() {
	switch (Robot::subEncodedArmLift->GetSwtCase()) {

		case 0 :
			Robot::subEncodedArmLift->Stop();
			break;
		case 1 :
			Robot::subEncodedArmLift->Reset();
			break;
		default :
			break;
		}
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdArmPosScale::Interrupted() {
	End();
}
