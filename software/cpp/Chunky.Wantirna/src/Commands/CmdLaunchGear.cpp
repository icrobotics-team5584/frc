#include <Commands/CmdLaunchGear.h>

CmdLaunchGear::CmdLaunchGear() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::subGearCatcher.get());
}

// Called just before this Command runs the first time
void CmdLaunchGear::Initialize() {
	Robot::subGearCatcher->PusherIn();
	Robot::subGearCatcher->DoorsClose();
}

// Called repeatedly when this Command is scheduled to run
void CmdLaunchGear::Execute() {
	Robot::subGearCatcher->PusherOut();
	Robot::subGearCatcher->DoorsOpen();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdLaunchGear::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdLaunchGear::End() {
	Robot::subGearCatcher->PusherIn();
	Robot::subGearCatcher->DoorsClose();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdLaunchGear::Interrupted() {
	End();
}
