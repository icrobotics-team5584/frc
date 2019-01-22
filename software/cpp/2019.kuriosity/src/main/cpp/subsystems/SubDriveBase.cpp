/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubDriveBase.h"
#include "Robot.h"
#include "commands/CmdJoystickDrive.h"

SubDriveBase::SubDriveBase() : Subsystem("ExampleSubsystem") {
  //motors
  _srxBackLeft = Robot::_robotMap->srxDriveBaseBackLeft;
  _srxBackRight = Robot::_robotMap->srxDriveBaseBackRight;
  _srxFrontRight = Robot::_robotMap->srxDriveBaseFrontRight;
  _srxFrontLeft = Robot::_robotMap->srxDriveBaseFrontLeft;
  difDrive.reset(new frc::DifferentialDrive(*_srxFrontLeft, *_srxFrontRight));

  //sensors
  _ahrsNavXGyro = Robot::_robotMap->ahrsNavXDriveBase;
  _clsMid = Robot::_robotMap->clsDriveBaseMid;
  _clsFront = Robot::_robotMap->clsDriveBaseFront;
  _ulsGimble = Robot::_robotMap->ulsDriveBaseGimble;
  _ulsBottom = Robot::_robotMap->ulsDriveBaseBottom;
  _clsLineLeft = Robot::_robotMap->clsLineDriveBaseLeft;
  _clsLineRight = Robot::_robotMap->clsLineDriveBaseRight;

  //encoders
  _srxBackRight->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
  _srxBackLeft->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
  _srxFrontRight->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
  _srxFrontLeft->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);

  _ulsGimble->SetAutomaticMode(true);
  _ulsBottom->SetAutomaticMode(true);

  // Robot constants
  metersPerRotation = 3.14159265359 * WHEEL_DIAMETER;
}
void SubDriveBase::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  SetDefaultCommand(new CmdJoystickDrive());
}

void SubDriveBase::drive(double speed, double rotation) {
  difDrive->ArcadeDrive(-speed, rotation);
}

void SubDriveBase::tankDrive(double leftSpeed, double rightSpeed) {
  difDrive->TankDrive(leftSpeed, rightSpeed);
}

double SubDriveBase::getRawLeftEncoder() {
  SmartDashboard::PutNumber("Left Encoder", _srxBackLeft->GetSelectedSensorPosition());
  return _srxBackLeft->GetSelectedSensorPosition(0);
}

double SubDriveBase::getRawRightEncoder() {
  SmartDashboard::PutNumber("Right Encoder", _srxFrontRight->GetSelectedSensorPosition());
  return -(_srxBackRight->GetSelectedSensorPosition(0));
}

double SubDriveBase::getVelocity() {
 return _srxBackLeft->GetSelectedSensorVelocity() * metersPerRotation;
}

void SubDriveBase::zeroEncoders() {
  _srxBackLeft->SetSelectedSensorPosition(0, 0);
  _srxBackRight->SetSelectedSensorPosition(0, 0);
}

double SubDriveBase::getDistanceTravelled() {
  double encoderTics = (getRawLeftEncoder() + getRawRightEncoder()) / 2;
  double wheelRotations = encoderTics / ENCODER_TICS_PER_ROTATION;
  double distance = wheelRotations * metersPerRotation;
  return distance;  
}

void SubDriveBase::resetYaw(){
  _ahrsNavXGyro->ZeroYaw();
}

double SubDriveBase::getYaw() {
  return _ahrsNavXGyro->GetYaw();
}

bool SubDriveBase::frontHasReachedLine() {
  SmartDashboard::PutNumber("frontHasReachedLine", not(_clsFront->Get()));
  return not(_clsFront->Get());
}

bool SubDriveBase::midHasReachedLine() {
  SmartDashboard::PutNumber("midHasReachedLine", not(_clsMid->Get()));
  return not(_clsMid->Get());
}

void SubDriveBase::brakeRobot() {
    difDrive->ArcadeDrive(-0.4, 0.2);
}

double SubDriveBase::getDistanceToObstical() {
  SmartDashboard::PutNumber("Bottom Ultrasonic Range", _ulsBottom->GetRangeMM());
  SmartDashboard::PutBoolean("Bottom Ultrasonic range valid?", _ulsBottom->IsRangeValid());
  return _ulsBottom->GetRangeMM();
}

//uses the ultrasonic sensor to check whether the cargo ship bay has a hatch panel on it
bool SubDriveBase::isBayEmpty() {
  if (_ulsGimble->GetRangeMM() < 500) {
    return false;
  }
  else {
    return true;
  }
}

bool SubDriveBase::isLeftClsOnLine() {
  return not(_clsLineLeft->Get());
}

bool SubDriveBase::isRightClsOnLine() {
  return not(_clsLineRight->Get());
}
