#include <Commands/CmdLaunchGear.h>

CmdLaunchGear::CmdLaunchGear() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::subGearCatcher.get());
	execounter = 0;
}

// Called just before this Command runs the first time
void CmdLaunchGear::Initialize() {
	Robot::subGearCatcher->PusherIn();
	Robot::subGearCatcher->DoorsClose();
	execounter = 0;
}

// Called repeatedly when this Command is scheduled to run
void CmdLaunchGear::Execute() {

	if( execounter >= 0 && execounter < 50 ) {
		Robot::subGearCatcher->DoorsOpen();
	}
	if( execounter >= 50 && execounter < 100 ) {
		Robot::subGearCatcher->PusherOut();
	}
	if( execounter >= 100 && execounter < 150 ) {
		Robot::subGearCatcher->PusherIn();
	}
	if( execounter >= 150 && execounter < 200 ) {
		Robot::subGearCatcher->DoorsClose();
	}
	execounter++;
}

// Make this return true when this Command no longer needs to run execute()
bool CmdLaunchGear::IsFinished() {
	if( execounter < 250 ) {
		return false;
	}
	return true;
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
