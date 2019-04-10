/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdStopAtLine.h"
#include "subsystems/SubDriveBase.h"

CmdStopAtLine::CmdStopAtLine(double speed) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subDriveBase.get());
  _speed = speed;
}

// Called just before this Command runs the first time
void CmdStopAtLine::Initialize() {
  Robot::subDriveBase->setTalBrakeMode(NeutralMode::Brake);
  initialAngle = Robot::subDriveBase->getYaw();
  
  leftLineCounter.SetUpSource(Robot::subDriveBase->getColourSensorReference(CLS_LEFT));
  rightLineCounter.SetUpSource(Robot::subDriveBase->getColourSensorReference(CLS_RIGHT));

}

// Called repeatedly when this Command is scheduled to run
void CmdStopAtLine::Execute() {
  currentAngle = Robot::subDriveBase->getYaw();
  desiredAngle = initialAngle + Robot::_oi->controller->GetX() * 5;
  Robot::subDriveBase->drive(_speed, kP * (desiredAngle - currentAngle));
}

// Make this return true when this Command no longer needs to run execute()
bool CmdStopAtLine::IsFinished() {
  bool leftLineFound = (leftLineCounter.Get() > 0);
  bool rightLineFound = (rightLineCounter.Get() > 0);
  return leftLineFound or rightLineFound; 
}

// Called once after isFinished returns true
void CmdStopAtLine::End() {
  leftLineCounter.Reset();
  rightLineCounter.Reset();
  Robot::subDriveBase->drive(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdStopAtLine::Interrupted() {}
