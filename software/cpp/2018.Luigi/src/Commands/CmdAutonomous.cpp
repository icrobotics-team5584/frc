#include "CmdAutonomous.h"

CmdAutonomous::CmdAutonomous() : MPController(RobotMap::subDriveBaseSRXleft, RobotMap::subDriveBaseSRXright, Robot::MPData)
{
	Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void CmdAutonomous::Initialize() {
	//Choose a motion profile
	std::string MP;
//	MP = autoSelector.DetermineMotionProfile(AutonomousSelector::Left);
	MP = "Middle-Switch-Left";	//use for a hard-coded motion profile

	//Reading in CSV
	Robot::MPData->ReadCSV(0, MP + "/" + MP + "_left.csv");
	Robot::MPData->ReadCSV(1, MP + "/" + MP + "_right.csv");

	//Initialise MPController
	MPController.initialise();
}

// Called repeatedly when this Command is scheduled to run
void CmdAutonomous::Execute() {
	MPController.execute();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdAutonomous::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdAutonomous::End() {
	MPController.stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdAutonomous::Interrupted() {
	End();
}
