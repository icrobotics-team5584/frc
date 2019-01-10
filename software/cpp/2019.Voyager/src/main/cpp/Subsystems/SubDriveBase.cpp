/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/SubDriveBase.h"
#include "Robot.h"
#include "Commands/CmdJoystickDrive.h"
#include <iostream>

SubDriveBase::SubDriveBase() : Subsystem("ExampleSubsystem"){
    cout << "Run drive base" << endl;
  //motor controllers
  _srxBackLeft = Robot::_robotMap->srxDriveBaseBackLeft;
  _srxBackRight = Robot::_robotMap->srxDriveBaseBackRight;
  _srxFrontRight = Robot::_robotMap->srxDriveBaseFrontRight;
  _srxFrontLeft = Robot::_robotMap->srxDriveBaseFrontLeft;

  difDrive.reset(new DifferentialDrive(*_srxFrontLeft, *_srxFrontRight));

  //sensors
  _ulsLeft = Robot::_robotMap->ulsDriveBaseLeft;
  _ulsLeft->SetAutomaticMode(true);
  // _ulsEchoLeft = Robot::_robotMap->ulsEchoDriveBaseLeft;
  _ahrsNavXGyro = Robot::_robotMap->ahrsDriveBaseNavXGyro;
  _clsLeft = Robot::_robotMap->clsDriveBaseLeft;
}

void SubDriveBase::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  //SetDefaultCommand(new CmdJoystickDrive());
}

void SubDriveBase::drive(double speed, double rotation) {
  difDrive->ArcadeDrive(speed, rotation);
}

//checks whether the bay on the cargo ship has a hatch panel on it
// bool SubDriveBase::isBayEmpty() {
//   SmartDashboard::PutBoolean("pls", getRange() > 500);
//   return getRange() > 500;
// }

void SubDriveBase::resetYaw(){
  _ahrsNavXGyro->ZeroYaw();
}

double SubDriveBase::getYaw() {
  return _ahrsNavXGyro->GetYaw();
}
bool SubDriveBase::hasReachedLine() {
  return not(_clsLeft->Get());
}
void SubDriveBase::brakeRobot() {
  difDrive->ArcadeDrive(-0.4, 0.2);
}
void SubDriveBase::getRange() {
  SmartDashboard::PutNumber("Ultrasonic Range", _ulsLeft->GetRangeMM());
  SmartDashboard::PutBoolean("Is range valid", _ulsLeft->IsRangeValid());
}