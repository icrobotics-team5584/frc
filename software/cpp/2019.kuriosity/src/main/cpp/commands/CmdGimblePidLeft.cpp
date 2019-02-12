#include "commands/CmdGimblePidLeft.h"
#include "Robot.h"

CmdGimblePidLeft::CmdGimblePidLeft() {
  Requires(Robot::subGimble.get());
}

// Called just before this Command runs the first time
void CmdGimblePidLeft::Initialize() {
  Robot::subGimble->PIDGimbleTo(90);
  std::cout << "GIMBLE PID LEFT" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void CmdGimblePidLeft::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdGimblePidLeft::IsFinished() { return true; }

// Called once after isFinished returns true
void CmdGimblePidLeft::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdGimblePidLeft::Interrupted() {
    End();
  }
