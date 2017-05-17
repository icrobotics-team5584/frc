#include <Commands/CmdGearDoorsOpen.h>

CmdGearDoorsOpen::CmdGearDoorsOpen() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::subGearCatcher.get());
}

// Called just before this Command runs the first time
void CmdGearDoorsOpen::Initialize() {
	Robot::subGearCatcher->DoorsOpen();
}

// Called repeatedly when this Command is scheduled to run
void CmdGearDoorsOpen::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CmdGearDoorsOpen::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdGearDoorsOpen::End() {
	Robot::subGearCatcher->DoorsClose();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdGearDoorsOpen::Interrupted() {
	End();
}
