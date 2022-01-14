// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubDriveBase.h"
#include "frc/smartdashboard/SmartDashboard.h"

SubDriveBase::SubDriveBase(){


	// Reset all the motor controllers to factory default
  _spmFrontLeft.RestoreFactoryDefaults();
  _spmFrontRight.RestoreFactoryDefaults();
  _spmBackLeft.RestoreFactoryDefaults();
  _spmBackRight.RestoreFactoryDefaults();

	// make back left follow front left and make back right follow front right
  _spmBackLeft.Follow(_spmFrontLeft);
  _spmBackRight.Follow(_spmFrontRight);

  metersPerRotation = pi * WHEEL_DIAMETER;
  _spmFrontRight.SetInverted(true);


}

void SubDriveBase::drive(double speed, double rotation, bool squaredInputs){
  _diffDrive.ArcadeDrive(speed, rotation, squaredInputs);
}

bool SubDriveBase::isNavxCal(){
  return ahrsNavXGyro.IsCalibrating();
}

double SubDriveBase::getYaw(){
  return ahrsNavXGyro.GetYaw();
}

double SubDriveBase::getDistanceTravelled(){
  double wheelRotations = _dollyWheel.GetPosition() / 2;
  frc::SmartDashboard::PutNumber("dolly rotations", wheelRotations);
  //double wheelRotations = _srxDolly.GetSelectedSensorPosition()/ENCODER_TICS_PER_ROTATION;
  double distance = wheelRotations * metersPerRotation;
  return distance;  
}

// This method will be called once per scheduler run
void SubDriveBase::Periodic() {
  frc::SmartDashboard::PutNumber("Encoder Position", _dollyWheel.GetPosition());
  frc::SmartDashboard::PutNumber("Encoder Velocity", _dollyWheel.GetVelocity());
}
