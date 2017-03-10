#include "CmdAutoMotionProfileToPeg.h"

CmdAutoMotionProfileToPeg::CmdAutoMotionProfileToPeg() : _example( * RobotMap::subDriveBaseTnxLeftMaster, * RobotMap::subDriveBaseTnxRightMaster )
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void CmdAutoMotionProfileToPeg::Initialize() {
	RobotMap::subDriveBaseTnxRightMaster->SetControlMode(CANTalon::kMotionProfile);
	RobotMap::subDriveBaseTnxLeftMaster->SetControlMode(CANTalon::kMotionProfile);
	firsttimearound = true;
}

// Called repeatedly when this Command is scheduled to run
void CmdAutoMotionProfileToPeg::Execute() {
	_example.control();
	CANTalon::SetValueMotionProfile setOutput = _example.getSetValue();
	RobotMap::subDriveBaseTnxRightMaster->Set(setOutput);
	RobotMap::subDriveBaseTnxLeftMaster->Set(setOutput);
	if( firsttimearound )
	{
		_example.start();
		firsttimearound = false;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool CmdAutoMotionProfileToPeg::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdAutoMotionProfileToPeg::End() {
	/* put motor controllers into a known state */
	RobotMap::subDriveBaseTnxRightMaster->SetControlMode(CANTalon::kPercentVbus);
	RobotMap::subDriveBaseTnxRightMaster->Set( 0 );
	RobotMap::subDriveBaseTnxLeftMaster->SetControlMode(CANTalon::kPercentVbus);
	RobotMap::subDriveBaseTnxLeftMaster->Set( 0 );
	/* clear our buffer and put everything into a known state */
	_example.reset();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdAutoMotionProfileToPeg::Interrupted() {
	End();
}
