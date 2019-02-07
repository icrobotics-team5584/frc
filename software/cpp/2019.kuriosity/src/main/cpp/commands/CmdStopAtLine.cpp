/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdStopAtLine.h"

CmdStopAtLine::CmdStopAtLine(double speed, ColourSensor colourSensor) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subDriveBase.get());
  _colourSensor = colourSensor;
  _speed = speed;
}

// Called just before this Command runs the first time
void CmdStopAtLine::Initialize() {
  Robot::subDriveBase->setTalBrakeMode(NeutralMode::Brake);
}

// Called repeatedly when this Command is scheduled to run
void CmdStopAtLine::Execute() {
  if (!Robot::subDriveBase->getColourSensor(_colourSensor)) {
    Robot::subDriveBase->drive(_speed, 0);
  } else {
    Robot::subDriveBase->drive(0, 0);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool CmdStopAtLine::IsFinished() { 
  return Robot::subDriveBase->getColourSensor(_colourSensor) or !Robot::_oi->btnStopAtLine->Get();
}

// Called once after isFinished returns true
void CmdStopAtLine::End() {
  Robot::subDriveBase->drive(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdStopAtLine::Interrupted() {}
