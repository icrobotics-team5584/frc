#include "CmdAuto_MotionProfile.h"

CmdAuto_MotionProfile::CmdAuto_MotionProfile(std::string profile) : MPController(RobotMap::subDriveBaseSRXleft, RobotMap::subDriveBaseSRXright, Robot::MPData)
{
	Robot::MPData->ReadMotionProfile(profile);
	Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void CmdAuto_MotionProfile::Initialize() {
	//Initialise MPController
	MPController.initialise();
}

// Called repeatedly when this Command is scheduled to run
void CmdAuto_MotionProfile::Execute() {
	MPController.execute();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdAuto_MotionProfile::IsFinished() {
	if (MPController.GetSetValue() == 0 /*Disabled*/){
		return true;
	} else {
		return false;
	}
}

// Called once after isFinished returns true
void CmdAuto_MotionProfile::End() {
	MPController.stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdAuto_MotionProfile::Interrupted() {
	End();
}
