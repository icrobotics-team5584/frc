#include <iostream>
#include "CmdArmPosExchange.h"

CmdArmPosExchange::CmdArmPosExchange() {
	std::cout << "created CmdArmPosExchange \n";
	Requires(Robot::subEncodedArmLift.get());

}

// Called just before this Command runs the first time
void CmdArmPosExchange::Initialize() {



}

// Called repeatedly when this Command is scheduled to run
void CmdArmPosExchange::Execute() {

	Robot::subEncodedArmLift->ArmToExchangePos();

}

// Make this return true when this Command no longer needs to run execute()
bool CmdArmPosExchange::IsFinished() {
	if(Robot::subIntake->GetSwitches()){
			return true;
		} else {
				return false;
			}
		}

// Called once after isFinished returns true
void CmdArmPosExchange::End() {
	Robot::subEncodedArmLift->CmdDefaStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdArmPosExchange::Interrupted() {

}
