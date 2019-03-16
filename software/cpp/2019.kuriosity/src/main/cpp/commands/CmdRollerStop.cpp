#include "commands/CmdRollerStop.h"
#include "Robot.h"

CmdRollerStop::CmdRollerStop() {
  Requires(Robot::subRollerIntake.get());
  Requires(Robot::subIntakeOutake.get());
  Requires(Robot::subPanelAffector.get());
}

// Called just before this Command runs the first time
void CmdRollerStop::Initialize() {
  Robot::subRollerIntake->Stop();
  Robot::subIntakeOutake->Stop();
  Robot::subPanelAffector->RetractFingers();
}

// Called repeatedly when this Command is scheduled to run
void CmdRollerStop::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdRollerStop::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdRollerStop::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdRollerStop::Interrupted() {}
