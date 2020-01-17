/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include "Robot.h"
#include "commands/CmdAutoEncoderDrive.h"
#include <iostream>
CmdAutoEncoderDrive::CmdAutoEncoderDrive(double target, double P, double I, double D, double Speed, double TargetY) {
  Requires(Robot::subDriveBase.get());
  _target = target;
  _P = P; 
  _I = I; 
  _D = D; 
  _Speed = Speed;
  _TargetY = TargetY;

  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CmdAutoEncoderDrive::Initialize() {
  if(Robot::posEncoderGyro->getPositionY() < _TargetY){
    isForward = true;
  } else{
    isForward = false;
  }
}

// Called repeatedly when this Command is scheduled to run
void CmdAutoEncoderDrive::Execute() {
  Robot::subDriveBase->autoEncoderDrive(_target, _P, _I, _D, _Speed);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdAutoEncoderDrive::IsFinished() {
  if(isForward){
    if(Robot::posEncoderGyro->getPositionY() < _TargetY){
      return false;
    } else{
      return true;
    }
  } else{
    if(Robot::posEncoderGyro->getPositionY() < _TargetY){
      return true;
    } else{
      return false; 
    }
  }
}

// Called once after isFinished returns true
void CmdAutoEncoderDrive::End() {
  Robot::subDriveBase->drive(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdAutoEncoderDrive::Interrupted() {
  End();
}
