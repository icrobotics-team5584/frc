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
  _spmFrontLeft.SetVoltage(left);
  _spmFrontRight.SetVoltage(right);
  _diffDrive.Feed();
}

void SubDriveBase::ResetEncoders() {
  _leftEncoder.SetPosition(0);
  _rightEncoder.SetPosition(0);
}

double SubDriveBase::GetAverageEncoderDistance() {
  return (_leftEncoder.GetPosition() + _rightEncoder.GetPosition()) / 2.0;
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
  return _gyro.GetYaw();
}

double SubDriveBase::GetTurnRate() {
  return -_gyro.GetRate();
}

frc::Pose2d SubDriveBase::GetPose() {
  return _odometry.GetPose();
}

frc::DifferentialDriveWheelSpeeds SubDriveBase::GetWheelSpeeds() {
  std::cout << _leftEncoder.GetVelocity() << "....." << _rightEncoder.GetVelocity() << std::endl;
  return {units::meters_per_second_t(_leftEncoder.GetVelocity()),
        units::meters_per_second_t(_rightEncoder.GetVelocity())};
}

void SubDriveBase::ResetOdometry(frc::Pose2d pose) {
  ResetEncoders();
  _odometry.ResetPosition(pose, frc::Rotation2d{(units::degree_t)_gyro.GetYaw()});
}

// This method will be called once per scheduler run
void SubDriveBase::Periodic() {
  _odometry.Update(frc::Rotation2d{(units::degree_t)_gyro.GetYaw()},
                    units::meter_t(_leftEncoder.GetPosition()),
                    units::meter_t(_rightEncoder.GetPosition()));
  _fieldSim.SetRobotPose(_odometry.GetPose());
  frc::SmartDashboard::PutNumber("Left Encoder", _leftEncoder.GetVelocity());
  frc::SmartDashboard::PutNumber("Right Encoder", _rightEncoder.GetVelocity());
  frc::SmartDashboard::PutNumber("Gyro Rotation", _gyro.GetYaw());
  frc::SmartDashboard::PutNumber("LEncoder pos", _leftEncoder.GetPosition());
  frc::SmartDashboard::PutNumber("REncoder pos", _rightEncoder.GetPosition());
  frc::SmartDashboard::PutNumber("Encoder Vol: ", (_leftEncoder.GetPosition()-encoderPos)/(timer.Get().value()-time));
  time = timer.Get().value();
  encoderPos = _leftEncoder.GetPosition();
}


void SubDriveBase::resetYaw(){
  _gyro.ZeroYaw();
}

bool SubDriveBase::isNavxCal(){
  return _gyro.IsCalibrating();
}
