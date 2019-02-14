#include "commands/CmdGimblePidRight.h"
#include "Robot.h"

CmdGimblePidRight::CmdGimblePidRight() {
  Requires(Robot::subGimble.get());
}

// Called just before this Command runs the first time
void CmdGimblePidRight::Initialize() {
  Robot::subGimble->PIDGimbleToRight();
  std::cout << "GIMBLE PID RIGHT" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void CmdGimblePidRight::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdGimblePidRight::IsFinished() { return true; }

// Called once after isFinished returns true
void CmdGimblePidRight::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdGimblePidRight::Interrupted() {
    End();
  }
