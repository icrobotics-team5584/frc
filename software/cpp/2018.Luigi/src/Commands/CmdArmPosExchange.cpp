#include <iostream>
#include "CmdArmPosExchange.h"

CmdArmPosExchange::CmdArmPosExchange() {
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
	return false;
}

// Called once after isFinished returns true
void CmdArmPosExchange::End() {
	std::cout << "deleted CmdArmPosExchange \n";
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdArmPosExchange::Interrupted() {

}
