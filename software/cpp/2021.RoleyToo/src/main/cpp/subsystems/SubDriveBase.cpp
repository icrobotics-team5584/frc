// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubDriveBase.h"
#include <frc/smartdashboard/SmartDashboard.h>
SubDriveBase::SubDriveBase() {
  metersPerRotation = pi * WHEEL_DIAMETER;

  _spmFrontLeft.RestoreFactoryDefaults();
  _spmFrontRight.RestoreFactoryDefaults();
  _spmBackLeft.RestoreFactoryDefaults();
  _spmBackRight.RestoreFactoryDefaults();

  _spmBackLeft.Follow(_spmFrontLeft);
  _spmBackRight.Follow(_spmFrontRight);

  _spmFrontLeft.SetSmartCurrentLimit(50);
  _spmFrontRight.SetSmartCurrentLimit(50);
  _spmBackLeft.SetSmartCurrentLimit(50);
  _spmBackRight.SetSmartCurrentLimit(50);
}

void SubDriveBase::drive(double speed, double rotation, bool squaredInputs){
  _diffDrive.ArcadeDrive(speed, rotation, squaredInputs);
}

// This method will be called once per scheduler run
void SubDriveBase::Periodic() {
  frc::SmartDashboard::PutNumber("navx", ahrsNavXGyro.GetYaw());
}


void SubDriveBase::deployDolly(){
  std::cout << "deploy dolly" << std::endl;
  solDollyAcuator.Set(frc::DoubleSolenoid::kForward);
}

void SubDriveBase::retractDolly(){
  std::cout << "retract dolly" << std::endl;
  solDollyAcuator.Set(frc::DoubleSolenoid::kReverse);
}

void SubDriveBase::zeroEncoders(){
  _spmFrontLeft.GetAlternateEncoder(rev::CANEncoder::AlternateEncoderType::kQuadrature, ENCODER_TICS_PER_ROTATION).SetPosition(0.0);
}

double SubDriveBase::getDistanceTravelled(){
  //double wheelRotations = _spmFrontLeft.GetAlternateEncoder(rev::CANEncoder::AlternateEncoderType::kQuadrature, ENCODER_TICS_PER_ROTATION).GetPosition();
  double wheelRotations = 0; //_srxDolly.GetSelectedSensorPosition()/ENCODER_TICS_PER_ROTATION;
  double distance = wheelRotations * metersPerRotation;
  return distance;  
}

void SubDriveBase::resetYaw(){
  ahrsNavXGyro.ZeroYaw();
}

bool SubDriveBase::isNavxCal(){
  return ahrsNavXGyro.IsCalibrating();
}

double SubDriveBase::getYaw(){
  return ahrsNavXGyro.GetYaw();
}