#include "commands/CmdDriveBaseSlow.h"
#include "Robot.h"

CmdDriveBaseSlow::CmdDriveBaseSlow() {
  Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void CmdDriveBaseSlow::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdDriveBaseSlow::Execute() {
  double x = Robot::_oi->controller->GetX();
  double y = Robot::_oi->controller->GetY();
  double axis = Robot::_oi->controller->GetRawAxis(leftAxisTrigger);
  SmartDashboard::PutNumber("axis test", axis);
  Robot::subDriveBase->drive(y/(axis + 1),x/(axis + 1));
}

// Make this return true when this Command no longer needs to run execute()
bool CmdDriveBaseSlow::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdDriveBaseSlow::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdDriveBaseSlow::Interrupted() {}
