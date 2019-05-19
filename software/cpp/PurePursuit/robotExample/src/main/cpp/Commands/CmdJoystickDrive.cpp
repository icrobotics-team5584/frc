#include "Commands/CmdJoystickDrive.h"
#include "Robot.h"

CmdJoystickDrive::CmdJoystickDrive() {
  // Declare subsystem dependencies
  Requires(Robot::subDriveBase.get());
  m_controller = Robot::oi->getController();
}

// Called just before this Command runs the first time
void CmdJoystickDrive::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void CmdJoystickDrive::Execute() {
  Robot::subDriveBase->drive(m_controller->GetY(), m_controller->GetX());
}

// Make this return true when this Command no longer needs to run execute()
bool CmdJoystickDrive::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdJoystickDrive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdJoystickDrive::Interrupted() {}
