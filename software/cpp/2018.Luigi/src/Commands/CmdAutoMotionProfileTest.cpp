#include <iostream>
#include "CmdAutoMotionProfileTest.h"

CmdAutoMotionProfileTest::CmdAutoMotionProfileTest()
: MPControl(RobotMap::subDriveBaseSRXleft, RobotMap::subDriveBaseSRXright, &kBaselineA[0][0], &kBaselineB[0][0], kMotionProfileSz)
{
//	std::cout << "CmdMPTest() CmdMPTest \n";
	Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void CmdAutoMotionProfileTest::Initialize() {
//	std::cout << "Initialize() CmdMPTest \n";
	MPControl.start();
}

// Called repeatedly when this Command is scheduled to run
void CmdAutoMotionProfileTest::Execute() {


}

// Make this return true when this Command no longer needs to run execute()
bool CmdAutoMotionProfileTest::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdAutoMotionProfileTest::End() {
	MPControl.stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdAutoMotionProfileTest::Interrupted() {
	End();
}
