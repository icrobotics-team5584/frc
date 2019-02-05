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
  _ulsLeft = Robot::_robotMap->ulsDriveBaseLeft;

  _ulsLeft->SetAutomaticMode(true);
  
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
void SubDriveBase::getRange() {
  SmartDashboard::PutNumber("Ultrasonic Range", _ulsLeft->GetRangeMM());
  SmartDashboard::PutBoolean("Is range valid", _ulsLeft->IsRangeValid());
}
//uses the ultrasonic sensor to check whether the cargo ship bay has a hatch panel on it
bool SubDriveBase::isBayEmpty() {
  if (_ulsLeft->GetRangeMM() < 500) {
    return false;
  }
  else {
    return true;
  }
}
void SubDriveBase::pidPositionConfig() {
  double kPIDLoopIdx = 0;
  double kTimeoutMs = 0;
   _srxFrontLeft->ConfigNominalOutputForward(0, kTimeoutMs);
  _srxFrontLeft->ConfigNominalOutputReverse(0, kTimeoutMs);
  _srxFrontLeft->ConfigPeakOutputForward(1, kTimeoutMs);
  _srxFrontLeft->ConfigPeakOutputReverse(-1, kTimeoutMs);

  _srxFrontLeft->Config_kP(kPIDLoopIdx, 0.0, kTimeoutMs); //0.046
  _srxFrontLeft->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
  _srxFrontLeft->Config_kD(kPIDLoopIdx, 0, kTimeoutMs);

  //right srx
  _srxFrontRight->ConfigNominalOutputForward(0, kTimeoutMs);
  _srxFrontRight->ConfigNominalOutputReverse(0, kTimeoutMs);
  _srxFrontRight->ConfigPeakOutputForward(1, kTimeoutMs);
  _srxFrontRight->ConfigPeakOutputReverse(-1, kTimeoutMs);

  _srxFrontRight->Config_kP(kPIDLoopIdx, 0.0, kTimeoutMs); //0.035
  _srxFrontRight->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
  _srxFrontRight->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);
  _srxFrontRight->SetNeutralMode(NeutralMode::Brake);
  _srxFrontLeft->SetNeutralMode(NeutralMode::Brake);
}

double SubDriveBase::positionPID(double distance) {
  _srxFrontLeft->Set(ControlMode::Position, distance);
  _srxFrontRight->Set(ControlMode::Position, distance);
} 