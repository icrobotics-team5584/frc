#include "commands/CmdEncoderDrive.h"
#include "Robot.h"

CmdEncoderDrive::CmdEncoderDrive(double distance) {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::subDriveBase.get());

  pidsrcEncoder.reset(new PidsrcEncoderDrive());
  pidoutEncoder.reset(new PidoutEncoderDrive());
  
  driveController.reset(new frc::PIDController(kP, kI, kD, pidsrcEncoder.get(), pidoutEncoder.get()));
  driveController->SetSetpoint(distance);
  driveController->SetAbsoluteTolerance(0.05);
  driveController->SetOutputRange(-0.8, 0.8);
  
  frc::SmartDashboard::PutData("Drive PID Controller", driveController.get());
}

// Called just before this Command runs the first time
void CmdEncoderDrive::Initialize() {
  Robot::subDriveBase->zeroEncoders();
  driveController->Enable();
}

// Called repeatedly when this Command is scheduled to run
void CmdEncoderDrive::Execute() {
  frc::SmartDashboard::PutNumber("error", driveController->GetError());
}

// Make this return true when this Command no longer needs to run execute()
bool CmdEncoderDrive::IsFinished() { 
  return driveController->OnTarget() or !Robot::_oi->btnSeekRocketSide->Get();// or Robot::subDriveBase->isRightClsOnLine();
}

// Called once after isFinished returns true
void CmdEncoderDrive::End() {
  driveController->Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdEncoderDrive::Interrupted() {
  End();
}
