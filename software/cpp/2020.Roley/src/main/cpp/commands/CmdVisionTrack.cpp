/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdVisionTrack.h"
#include "Robot.h"
#include "frc/smartdashboard/SmartDashboard.h"

CmdVisionTrack::CmdVisionTrack() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void CmdVisionTrack::Initialize() {
  P = frc::SmartDashboard::GetNumber("Vision P", 0);
  I = frc::SmartDashboard::GetNumber("Vision I", 0);
  D = frc::SmartDashboard::GetNumber("Vision D", 0);
  _cap = frc::SmartDashboard::GetNumber("Vision Speed Cap", 0);
  _maxIntegral = frc::SmartDashboard::GetNumber("Vision Integral Cap", 0);
  _error = Robot::ntTable->GetNumber("pegx", 0);
}

// Called repeatedly when this Command is scheduled to run
void CmdVisionTrack::Execute() {
  _error = Robot::ntTable->GetNumber("pegx", 0);

  if (_integral > _maxIntegral)
  {
    _integral = _maxIntegral;
  }
  if (_integral < -_maxIntegral)
  {
    _integral = -_maxIntegral;
  }

  _derivative = _error - _lastError;

  _speed = (_error * P) + (_integral * I) + (_derivative * D);

  if (_speed > _cap)
  {
    _speed = _cap;
  }
  if (_speed < -_cap)
  {
    _speed = -_cap;
  }
  

  frc::SmartDashboard::PutNumber("Vision Output Speed", _speed);
  Robot::subDriveBase->drive(Robot::oi->getJoystickY(), _speed, false);


  _integral += _error;
}

// Make this return true when this Command no longer needs to run execute()
bool CmdVisionTrack::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdVisionTrack::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdVisionTrack::Interrupted() {}
