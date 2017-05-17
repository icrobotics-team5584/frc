#include <Commands/CmdGearPusher.h>

CmdGearPusher::CmdGearPusher() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::subGearCatcher.get());
}

// Called just before this Command runs the first time
void CmdGearPusher::Initialize() {
	Robot::subGearCatcher->PusherOut();
}

// Called repeatedly when this Command is scheduled to run
void CmdGearPusher::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CmdGearPusher::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdGearPusher::End() {
	Robot::subGearCatcher->PusherIn();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdGearPusher::Interrupted() {
	End();
}
