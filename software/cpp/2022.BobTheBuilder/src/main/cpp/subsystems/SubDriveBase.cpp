// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubDriveBase.h"

SubDriveBase::SubDriveBase(){
	// Reset all the motor controllers to factory default
  _spmFrontLeft.RestoreFactoryDefaults();
  _spmFrontRight.RestoreFactoryDefaults();
  _spmBackLeft.RestoreFactoryDefaults();
  _spmBackRight.RestoreFactoryDefaults();

	// make back left follow front left and make back right follow front right
  _spmBackLeft.Follow(_spmFrontLeft);
  _spmBackRight.Follow(_spmFrontRight);

  // Invert Front left spark max
  _spmFrontLeft.SetInverted(true);

  // Initialize left and right encoders
  _leftEncoder.SetDistancePerPulse(kEncoderDistancePerPulse);
  _rightEncoder.SetDistancePerPulse(kEncoderDistancePerPulse);

}

void SubDriveBase::drive(double speed, double rotation, bool squaredInputs){
  _diffDrive.ArcadeDrive(speed, rotation, squaredInputs);
}

frc::DifferentialDriveWheelSpeeds SubDriveBase::GetWheelSpeeds() {
  return {units::meters_per_second_t(_leftEncoder.GetRate()),
        units::meters_per_second_t(_rightEncoder.GetRate())};
}

// This method will be called once per scheduler run
void SubDriveBase::Periodic() {}
