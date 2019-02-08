/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdStopAtLine.h"

CmdStopAtLine::CmdStopAtLine(double speed, ColourSensor rightColourSensor, ColourSensor leftColourSensor) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subDriveBase.get());
  Requires(Robot::subGimble.get());
  _rightColourSensor = rightColourSensor;
  _leftColourSensor = leftColourSensor;
  _speed = speed;
}

// Called just before this Command runs the first time
void CmdStopAtLine::Initialize() {
  Robot::subDriveBase->setTalBrakeMode(NeutralMode::Brake);
  initialAngle = Robot::subDriveBase->getYaw();

}

// Called repeatedly when this Command is scheduled to run
void CmdStopAtLine::Execute() {
  currentAngle = Robot::subDriveBase->getYaw();
  if (!Robot::subDriveBase->getColourSensor(_rightColourSensor) or !Robot::subDriveBase->getColourSensor(_leftColourSensor)) {
    frc::SmartDashboard::PutNumber("speed", _speed);
    Robot::subDriveBase->drive(_speed, kP * (initialAngle - currentAngle));
  } else {
    Robot::subDriveBase->drive(0, 0);
    if(Robot::subDriveBase->getColourSensor(_rightColourSensor)) {
      //Robot::subGimble->right();
      frc::SmartDashboard::PutBoolean("right", true);
      frc::SmartDashboard::PutBoolean("left", false);

    }
    else {
      frc::SmartDashboard::PutBoolean("left", true);
      frc::SmartDashboard::PutBoolean("right", false);
      //Robot::subGimble->left();
    }
  }
}

// Make this return true when this Command no longer needs to run execute()
bool CmdStopAtLine::IsFinished() { 
  return Robot::subDriveBase->getColourSensor(_rightColourSensor) or Robot::subDriveBase->getColourSensor(_leftColourSensor) or !Robot::_oi->btnSeekRocketSide->Get();
}

// Called once after isFinished returns true
void CmdStopAtLine::End() {
  Robot::subDriveBase->drive(0, 0);
  frc::SmartDashboard::PutNumber("speed", 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdStopAtLine::Interrupted() {}
