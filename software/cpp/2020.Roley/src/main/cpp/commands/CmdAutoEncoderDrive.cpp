/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include <iostream>
#include "Robot.h"
#include "commands/CmdAutoEncoderDrive.h"

CmdAutoEncoderDrive::CmdAutoEncoderDrive(PIDAutoConfig _PIDConfig) {
  //Use "AutoRoutine" + desired routine + "Leg" + desired part of said routine
  //For example CmdAutoEncoderDrive(autoRoutineOneLegOne)
  //will run the first part of routine one
  Requires(Robot::subDriveBase.get());
  //PID variables assigned values from passed in structure
  //find values of structures at "Utilities/AutoPIDConfig.cpp"
  _target = _PIDConfig.targetX;//position of the target line left and right of the robot
  _P = _PIDConfig.P; 
  _I = _PIDConfig.I; 
  _D = _PIDConfig.D; 
  _Speed = _PIDConfig.speed;//speed of the robot
  _TargetY = _PIDConfig.targetY;  // position of the end of the target line 
}

// Called just before this Command runs the first time
void CmdAutoEncoderDrive::Initialize() {
  //checks which direction the robot will be going so it knows when it has reached the target
  if(Robot::posEncoderGyro->getPositionY() < _TargetY){
    isForward = true;
  } else{
    isForward = false;
  }
}

// Called repeatedly when this Command is scheduled to run
void CmdAutoEncoderDrive::Execute() {
  Robot::subDriveBase->autoEncoderDrive(_target, _P, _I, _D, _Speed);//runs the PID from SubDriveBase.cpp
}

// Make this return true when this Command no longer needs to run execute()
bool CmdAutoEncoderDrive::IsFinished() {
  if(isForward){//checks which direction the robot is going as calculated in CmdAutoEncoderDrive::Initialize()
    if(Robot::posEncoderGyro->getPositionY() < _TargetY){//checks whether robot has reached destination
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
  Robot::subDriveBase->drive(0, 0);//robot stops (duh)
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdAutoEncoderDrive::Interrupted() {
  End();
}

