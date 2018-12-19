#include "CmdAuto_MotionProfile.h"


CmdAuto_MotionProfile::CmdAuto_MotionProfile(std::string profile, int profileTimeout) : MPController(RobotMap::subDriveBaseSRXleft, RobotMap::subDriveBaseSRXright, profile, profileTimeout)
{
	std::cout << "CmdAuto_MotionProfile: Constructor Start (" << profile << ")" << std::endl;
	_profile = profile;
	Requires(Robot::subDriveBase.get());
	std::cout << "CmdAuto_MotionProfile: Constructor Finish (" << profile << ")" << std::endl;
}

// Called just before this Command runs the first time
void CmdAuto_MotionProfile::Initialize() {
	std::cout << "CmdAuto_MotionProfile: Initialise Start (" << _profile << ")" << std::endl;
	std::cout << "CmdAuto_MotionProfile: Loading MP" << std::endl;
	MPController.load();
	std::cout << "CmdAuto_MotionProfile: Driving MP" << std::endl;
	//Initialise MPController
	MPController.initialise();
	std::cout << "CmdAuto_MotionProfile: Initialise Finish (" << _profile << ")" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void CmdAuto_MotionProfile::Execute() {
	MPController.execute();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdAuto_MotionProfile::IsFinished() {
	if (not MPController.IsRunning()){
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
