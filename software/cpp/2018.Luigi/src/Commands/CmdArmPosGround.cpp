#include "CmdArmPosGround.h"

CmdArmPosGround::CmdArmPosGround() {

	Requires(Robot::subEncodedArmLift.get());

}

// Called just before this Command runs the first time
void CmdArmPosGround::Initialize() {



}

// Called repeatedly when this Command is scheduled to run
void CmdArmPosGround::Execute() {

	Robot::subEncodedArmLift->ArmToGroundPos();

}

// Make this return true when this Command no longer needs to run execute()
bool CmdArmPosGround::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdArmPosGround::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdArmPosGround::Interrupted() {

}
