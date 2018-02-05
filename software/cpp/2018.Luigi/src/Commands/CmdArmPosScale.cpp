#include "CmdArmPosScale.h"
#include <iostream>

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
	std::cout << "CMD SCA IS_FINISHED" << std::endl;
	if(Robot::subEncodedArmLift->GetSwitches()){
			std::cout << "TRUE CMD scale" << std::endl;
			return true;
		} else {
			std::cout << "FALSE CMD scale" << std::endl;
			return false;
			}
		}

// Called once after isFinished returns true
void CmdArmPosScale::End() {
	std::cout << "CMD scale END" << std::endl;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdArmPosScale::Interrupted() {

}
