// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubDriveBase.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>

SubDriveBase::SubDriveBase(){
	// Reset all the motor controllers to factory default
  _spmFrontLeft.RestoreFactoryDefaults();
  _spmFrontRight.RestoreFactoryDefaults();
  _spmBackLeft.RestoreFactoryDefaults();
  _spmBackRight.RestoreFactoryDefaults();
  _spmFrontLeft.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  _spmFrontRight.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  _spmBackLeft.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  _spmBackRight.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

	// make back left follow front left and make back right follow front right
  _spmBackLeft.Follow(_spmFrontLeft);
  _spmBackRight.Follow(_spmFrontRight);

  // Invert Front left spark max
  _spmFrontLeft.SetInverted(true);

  // Initialize left and right encoders
  ResetEncoders();
  _leftEncoder.SetPositionConversionFactor(kEncoderDistancePerPulse);
  _rightEncoder.SetPositionConversionFactor(kEncoderDistancePerPulse);
  _leftEncoder.SetVelocityConversionFactor(kEncoderVelocityPerPulse);
  _rightEncoder.SetVelocityConversionFactor(kEncoderVelocityPerPulse);
  frc::SmartDashboard::PutData("Field", &_fieldSim);

  timer.Start();

}

void SubDriveBase::drive(double speed, double rotation, bool squaredInputs){
  _diffDrive.ArcadeDrive(speed, rotation, squaredInputs);
}

void SubDriveBase::TankDriveVolts(units::volt_t left, units::volt_t right) {
  std::cout << left.value() << "/n" << right.value() << "/n" << std::endl;
  _spmFrontLeft.SetVoltage(-left);
  _spmFrontRight.SetVoltage(-right);
  _diffDrive.Feed();
}

void SubDriveBase::ResetEncoders() {
  _leftEncoder.SetPosition(0);
  _rightEncoder.SetPosition(0);
}

double SubDriveBase::GetAverageEncoderDistance() {
  return (getLeftPos() + getRightPos()) / 2.0;
}

rev::RelativeEncoder& SubDriveBase::GetLeftEncoder() {
  return _leftEncoder;
}

rev::RelativeEncoder& SubDriveBase::GetRightEncoder() {
  return _rightEncoder;
}

void SubDriveBase::SetMaxOutput(double maxOutput) {
  _diffDrive.SetMaxOutput(maxOutput);
}

float SubDriveBase::GetHeading(){
  return -_gyro.GetYaw();
}

double SubDriveBase::GetTurnRate() {
  return -_gyro.GetRate();
}

frc::Pose2d SubDriveBase::GetPose() {
  return _odometry.GetPose();
}

frc::DifferentialDriveWheelSpeeds SubDriveBase::GetWheelSpeeds() {
  return {units::meters_per_second_t(getLeftVel()),
        units::meters_per_second_t(getRightVel())};
}

void SubDriveBase::ResetOdometry(frc::Pose2d pose) {
  ResetEncoders();
  _odometry.ResetPosition(pose, frc::Rotation2d{(units::degree_t)GetHeading()});
}

// This method will be called once per scheduler run
void SubDriveBase::Periodic() {
  _odometry.Update(frc::Rotation2d{(units::degree_t)GetHeading()},
                    units::meter_t(getLeftPos()),
                    units::meter_t(getRightPos()));
  _fieldSim.SetRobotPose(_odometry.GetPose());
  frc::SmartDashboard::PutNumber("Left Encoder", getLeftVel());
  frc::SmartDashboard::PutNumber("Right Encoder", getRightVel());
  frc::SmartDashboard::PutNumber("Gyro Rotation", GetHeading());
  frc::SmartDashboard::PutNumber("LEncoder pos", getLeftPos());
  frc::SmartDashboard::PutNumber("REncoder pos", getRightPos());
  frc::SmartDashboard::PutNumber("Encoder Vol: ", (getLeftPos()-encoderPos)/(timer.Get().value()-time));
  time = timer.Get().value();
  encoderPos = getLeftPos();
}


void SubDriveBase::resetYaw(){
  _gyro.ZeroYaw();
}

bool SubDriveBase::isNavxCal(){
  return _gyro.IsCalibrating();
}

double SubDriveBase::getLeftPos() {
  return -_leftEncoder.GetPosition();
}

double SubDriveBase::getRightPos() {
  return -_rightEncoder.GetPosition();  
}

double SubDriveBase::getLeftVel() {
  return -_leftEncoder.GetVelocity();
}

double SubDriveBase::getRightVel() {
  return -_rightEncoder.GetVelocity();
}
