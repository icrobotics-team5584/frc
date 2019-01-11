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
  _srxBackLeft = Robot::_robotMap->srxDriveBaseBackLeft;
  _srxBackRight = Robot::_robotMap->srxDriveBaseBackRight;
  _srxFrontRight = Robot::_robotMap->srxDriveBaseFrontRight;
  _srxFrontLeft = Robot::_robotMap->srxDriveBaseFrontLeft;
  difDrive.reset(new frc::DifferentialDrive(*_srxFrontLeft, *_srxFrontRight));

  _ahrsNavXGyro = Robot::_robotMap->ahrsNavXDriveBase;
  _clsMid = Robot::_robotMap->clsDriveBaseMid;
  _clsFront = Robot::_robotMap->clsDriveBaseFront;
  }

void SubDriveBase::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  SetDefaultCommand(new CmdJoystickDrive());
}

void SubDriveBase::drive(double speed, double rotation) {
  difDrive->ArcadeDrive(speed, rotation);
}

void SubDriveBase::resetYaw(){
  _ahrsNavXGyro->ZeroYaw();
}

double SubDriveBase::getYaw() {
  return _ahrsNavXGyro->GetYaw();
}
bool SubDriveBase::hasReachedLine() {
  return not(_clsFront->Get());
}
void SubDriveBase::brakeRobot() {
    difDrive->ArcadeDrive(-0.4, 0.2);
}
void SubDriveBase::getRange() {
  SmartDashboard::PutNumber("Ultrasonic Range", _ulsLeft->GetRangeMM());
  SmartDashboard::PutBoolean("Is range valid", _ulsLeft->IsRangeValid());
}
void SubDriveBase::getClsData() {
  SmartDashboard::PutNumber("Black Colour Sensor Value", _clsMid->GetValue());
  SmartDashboard::PutNumber("Black Colour Sensor Voltage", _clsMid->GetVoltage());
}