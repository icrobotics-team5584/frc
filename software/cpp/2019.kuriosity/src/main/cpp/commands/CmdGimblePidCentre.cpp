#include "commands/CmdGimblePidCentre.h"
#include "Robot.h"

CmdGimblePidCentre::CmdGimblePidCentre() {
  Requires(Robot::subGimble.get());
  Requires(Robot::subGimbleLimits.get());
}

// Called just before this Command runs the first time
void CmdGimblePidCentre::Initialize() {
  Robot::subGimble->ToCentre();
  
  //std::cout << "GIMBLE PID CENTRE" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void CmdGimblePidCentre::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdGimblePidCentre::IsFinished() { return true; }

// Called once after isFinished returns true
void CmdGimblePidCentre::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdGimblePidCentre::Interrupted() {
  End();
}
