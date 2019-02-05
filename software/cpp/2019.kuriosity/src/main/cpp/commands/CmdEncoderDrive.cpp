#include "commands/CmdEncoderDrive.h"
#include "Robot.h"

CmdEncoderDrive::CmdEncoderDrive() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::subDriveBase.get());

  pidsrcEncoder.reset(new PidsrcEncoderDrive());
  // driveController.reset(new frc::PIDController(kP, kI, kD, pidsrcEncoder.get(), ));
}

// Called just before this Command runs the first time
void CmdEncoderDrive::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdEncoderDrive::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdEncoderDrive::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdEncoderDrive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdEncoderDrive::Interrupted() {}
