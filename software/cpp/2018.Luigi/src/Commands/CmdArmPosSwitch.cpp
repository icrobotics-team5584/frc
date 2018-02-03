#include "CmdArmPosSwitch.h"

CmdArmPosSwitch::CmdArmPosSwitch() {
	std::cout << "Created CmdArmPosSwitch" << std::endl;
	Requires(Robot::subEncodedArmLift.get());

}

// Called just before this Command runs the first time
void CmdArmPosSwitch::Initialize() {
	std::cout << "Running CmdArmPosSwitch::Initialize()" << std::endl;


}

// Called repeatedly when this Command is scheduled to run
void CmdArmPosSwitch::Execute() {

	Robot::subEncodedArmLift->ArmToSwitchPos();

}

// Make this return true when this Command no longer needs to run execute()
bool CmdArmPosSwitch::IsFinished() {
	if (Robot::subEncodedArmLift->GetCurrentPosition() == Robot::subEncodedArmLift->GetTargetPosition()){
		//stop command if target position is reached
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void CmdArmPosSwitch::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdArmPosSwitch::Interrupted() {

}
