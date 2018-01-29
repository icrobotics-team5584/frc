#include "CmdAutonomous.h"

CmdAutonomous::CmdAutonomous() : MPController(RobotMap::subDriveBaseSRXleft, RobotMap::subDriveBaseSRXright, Robot::MPData)
{
	std::cout << "Running CmdAutonomous::CmdAutonomous()" << std::endl;
	Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void CmdAutonomous::Initialize() {
	std::cout << "Running CmdAutonomous::Initialize()" << std::endl;

	//Choose a motion profile
	std::string MP;
//	MP = autoSelector.DetermineMotionProfile(AutonomousSelector::Left);
	MP = "Left-Switch-Left";

	//Reading in CSV
	std::cout << "reading in CSV: '" << MP << "_left.csv'" << std::endl;
	Robot::MPData->ReadCSV(0, MP + "_left.csv");
	std::cout << "reading in CSV: '" << MP << "_right.csv'" << std::endl;
	Robot::MPData->ReadCSV(1, MP + "_right.csv");

	//Initialise MPController
	std::cout << "About to run MPController.initialise()" << std::endl;
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

}
