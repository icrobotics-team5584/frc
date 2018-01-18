#include "CmdAutoMotionProfileTest.h"

CmdAutoMotionProfileTest::CmdAutoMotionProfileTest()
: MPControl(RobotMap::subDriveBaseSRXleft, RobotMap::subDriveBaseSRXright, MPLtest, MPRtest, kMotionProfileSz)
{
	Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void CmdAutoMotionProfileTest::Initialize() {
	MPControl.start();
}

// Called repeatedly when this Command is scheduled to run
void CmdAutoMotionProfileTest::Execute() {
	MPControl.control();

	SetValueMotionProfile setOutput = MPControl.GetSetValue();
	RobotMap::subDriveBaseSRXleft->Set(ControlMode::MotionProfile, setOutput);
	RobotMap::subDriveBaseSRXright->Set(ControlMode::MotionProfile, setOutput);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdAutoMotionProfileTest::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdAutoMotionProfileTest::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdAutoMotionProfileTest::Interrupted() {

}
