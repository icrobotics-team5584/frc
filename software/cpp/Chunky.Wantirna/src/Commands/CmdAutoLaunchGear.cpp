#include <Commands/CmdAutoLaunchGear.h>

CmdAutoLaunchGear::CmdAutoLaunchGear() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::subGearCatcher.get());
	execounter = 0;
	finished = false;
}

// Called just before this Command runs the first time
void CmdAutoLaunchGear::Initialize() {
	Robot::subGearCatcher->PusherIn();
	Robot::subGearCatcher->DoorsClose();
	execounter = 0;
	finished = false;
}

// Called repeatedly when this Command is scheduled to run
void CmdAutoLaunchGear::Execute() {

	if( execounter >= 25 && execounter < 75 ) {
		Robot::subGearCatcher->DoorsOpen();
	}
	if( execounter >= 75 ) {
		Robot::subGearCatcher->PusherOut();
		finished = true;
	}
	execounter++;
}

// Make this return true when this Command no longer needs to run execute()
bool CmdAutoLaunchGear::IsFinished() {
	if( finished ) {
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void CmdAutoLaunchGear::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdAutoLaunchGear::Interrupted() {
	End();
}
