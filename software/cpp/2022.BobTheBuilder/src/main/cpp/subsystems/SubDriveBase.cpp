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

	// Set Current Limiting on all drive motors
  _spmFrontLeft.SetSmartCurrentLimit(_currentLimit);
  _spmFrontRight.SetSmartCurrentLimit(_currentLimit);
  _spmBackLeft.SetSmartCurrentLimit(_currentLimit);
  _spmBackRight.SetSmartCurrentLimit(_currentLimit);

	// make back left follow front left and make back right follow front right
  _spmBackLeft.Follow(_spmFrontLeft);
  _spmBackRight.Follow(_spmFrontRight);

  metersPerRotation = pi * WHEEL_DIAMETER;
  _spmFrontRight.SetInverted(true);

  SetBreakMode();
  SetRampRate(RAMP_RATE);

  frc::SmartDashboard::PutNumber("LimelightP", 0.005);
  frc::SmartDashboard::PutNumber("LimelightI", 0.0);
  frc::SmartDashboard::PutNumber("LimelightD", 0.0001);
  frc::SmartDashboard::PutNumber("LimelightF", 0.08);

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

void SubDriveBase::resetYaw(){
  ahrsNavXGyro.ZeroYaw();
}

void SubDriveBase::deployDolly(){
  solDolly.Set(frc::DoubleSolenoid::Value::kForward);
}

void SubDriveBase::retractDolly(){
  solDolly.Set(frc::DoubleSolenoid::Value::kReverse);
}

double SubDriveBase::getDistanceTravelled(){
  // double wheelRotations = _talonDolly.GetSelectedSensorPosition() / 2;

  double wheelRotations = _dollyWheel.GetPosition()/2;
  frc::SmartDashboard::PutNumber("dolly rotations", wheelRotations);
  double distance = wheelRotations * metersPerRotation;
  return distance;  
}

double SubDriveBase::GetTalonDistanceTravelled() {
  double encoderTics = _dollyWheel.GetPosition();
  double wheelRotations = encoderTics / ENCODER_TICS_PER_ROTATION;
  double distance = wheelRotations * metersPerRotation;
  return distance;  
}

// This method will be called once per scheduler run
void SubDriveBase::Periodic() {
  frc::SmartDashboard::PutNumber("Encoder Position", GetTalonDistanceTravelled());
  frc::SmartDashboard::PutNumber("Encoder Velocity", _dollyWheel.GetVelocity());
}

void SubDriveBase::SetCoastMode() {
  _spmFrontLeft.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
  _spmFrontRight.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
  _spmBackLeft.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
  _spmBackRight.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
}


void SubDriveBase::SetBreakMode() {
  _spmFrontLeft.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  _spmFrontRight.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  _spmBackLeft.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  _spmBackRight.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
}


void SubDriveBase::SetRampRate(double rampRate) {
  _spmFrontLeft.SetOpenLoopRampRate(rampRate);
  _spmFrontRight.SetOpenLoopRampRate(rampRate);
  _spmBackLeft.SetOpenLoopRampRate(rampRate);
  _spmBackRight.SetOpenLoopRampRate(rampRate);
}