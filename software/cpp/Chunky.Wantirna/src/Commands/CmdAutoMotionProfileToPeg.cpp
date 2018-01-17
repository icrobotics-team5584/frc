#include "CmdAutoMotionProfileToPeg.h"

CmdAutoMotionProfileToPeg::CmdAutoMotionProfileToPeg(int profile) :
_example( * RobotMap::subDriveBaseTnxLeftMaster, * RobotMap::subDriveBaseTnxRightMaster, profile)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::subDriveBase.get());
	execounter = 0;
}

// Called just before this Command runs the first time
void CmdAutoMotionProfileToPeg::Initialize() {
	RobotMap::subDriveBaseTnxRightMaster->Set(ControlMode::MotionProfile, 0);
	RobotMap::subDriveBaseTnxLeftMaster->Set(ControlMode::MotionProfile, 0);
	firsttimearound = true;
	execounter = 0;
}

// Called repeatedly when this Command is scheduled to run
void CmdAutoMotionProfileToPeg::Execute() {
	_example.control();
	SetValueMotionProfile setOutput = _example.getSetValue();
	RobotMap::subDriveBaseTnxRightMaster->Set(ControlMode::MotionProfile, setOutput);
	RobotMap::subDriveBaseTnxLeftMaster->Set(ControlMode::MotionProfile, setOutput);
	if( firsttimearound )
	{
		_example.start();
		firsttimearound = false;
	}
    execounter++;
}

// Make this return true when this Command no longer needs to run execute()
bool CmdAutoMotionProfileToPeg::IsFinished() {
	if( ! _example.hasBeenStarted() ) {
		// MP has not commenced yet so this command is not finished
		return false;
	}
	if( execounter < 100 ) {
		// MP has not had a chance to start yet so this command is not finished
		return false;
	}
	if( _example.getState() ) {
		// MP is in progress but has not completed yet so this command is not finished
		return false;
	}
	return true;
}

// Called once after isFinished returns true
void CmdAutoMotionProfileToPeg::End() {
	/* put motor controllers into a known state */
	RobotMap::subDriveBaseTnxRightMaster->Set(ControlMode::PercentOutput, 0);
	RobotMap::subDriveBaseTnxLeftMaster->Set(ControlMode::PercentOutput, 0);
	/* clear our buffer and put everything into a known state */
	_example.reset();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdAutoMotionProfileToPeg::Interrupted() {
	End();
}
