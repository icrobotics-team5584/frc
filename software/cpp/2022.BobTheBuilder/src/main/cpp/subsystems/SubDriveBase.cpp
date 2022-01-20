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

  ResetEncoders();
}

void SubDriveBase::drive(double speed, double rotation, bool squaredInputs){
  _diffDrive.ArcadeDrive(speed, rotation, squaredInputs);
}

void SubDriveBase::TankDriveVolts(units::volt_t left, units::volt_t right) {
  _spmFrontLeft.SetVoltage(left);
  _spmFrontRight.SetVoltage(right);
  _diffDrive.Feed();
}

void SubDriveBase::ResetEncoders() {
  _leftEncoder.Reset();
  _rightEncoder.Reset();
}

double SubDriveBase::GetAverageEncoderDistance() {
  return (_leftEncoder.GetDistance() + _rightEncoder.GetDistance()) / 2.0;
}

frc::Encoder& SubDriveBase::GetLeftEncoder() {
  return _leftEncoder;
}

frc::Encoder& SubDriveBase::GetRightEncoder() {
  return _rightEncoder;
}

void SubDriveBase::SetMaxOutput(double maxOutput) {
  _diffDrive.SetMaxOutput(maxOutput);
}

units::degree_t SubDriveBase::GetHeading() const {
  return _gyro.GetRotation2d().Degrees();
}

double SubDriveBase::GetTurnRate() {
  return -_gyro.GetRate();
}

frc::Pose2d SubDriveBase::GetPose() {
  return _odometry.GetPose();
}

frc::DifferentialDriveWheelSpeeds SubDriveBase::GetWheelSpeeds() {
  return {units::meters_per_second_t(_leftEncoder.GetRate()),
        units::meters_per_second_t(_rightEncoder.GetRate())};
}

void SubDriveBase::ResetOdometry(frc::Pose2d pose) {
  ResetEncoders();
  _odometry.ResetPosition(pose, _gyro.GetRotation2d());
}

// This method will be called once per scheduler run
void SubDriveBase::Periodic() {}
