#include "commands/CmdElevatorLimit.h"

CmdElevatorLimit::CmdElevatorLimit() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CmdElevatorLimit::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdElevatorLimit::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdElevatorLimit::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdElevatorLimit::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdElevatorLimit::Interrupted() {}
