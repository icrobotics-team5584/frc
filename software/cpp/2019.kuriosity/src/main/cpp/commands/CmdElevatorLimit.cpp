#include "commands/CmdElevatorLimit.h"

CmdElevatorLimit::CmdElevatorLimit() {
  Requires(Robot::subElevator.get());
}

// Called just before this Command runs the first time
void CmdElevatorLimit::Initialize() {
  Robot::subElevator->TestingPID();
}

// Called repeatedly when this Command is scheduled to run
void CmdElevatorLimit::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdElevatorLimit::IsFinished() { return true; }

// Called once after isFinished returns true
void CmdElevatorLimit::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdElevatorLimit::Interrupted() {
  End();
}
