// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubTurret.h"

SubTurret::SubTurret() {
  _networktables = nt::NetworkTableInstance::GetDefault();
  _limelight = _networktables.GetTable("limelight");
  LimeLEDOff();

  _spmFlywheelRight.RestoreFactoryDefaults();
  _spmFlywheelLeft.RestoreFactoryDefaults();
  _spmTurret.RestoreFactoryDefaults();
  _spmHood.RestoreFactoryDefaults();

  _spmFlywheelRight.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
  _spmFlywheelLeft.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
  _spmTurret.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  _spmHood.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

  _spmFlywheelLeft.Follow(_spmFlywheelRight, true);

  _spmFlywheelRight.SetSmartCurrentLimit(50);
  _spmFlywheelLeft.SetSmartCurrentLimit(50);
  _spmTurret.SetSmartCurrentLimit(20);
  _spmHood.SetSmartCurrentLimit(20);

  _spmHood.SetInverted(true);

  _encHood.SetPosition(0);

  frc::SmartDashboard::PutNumber("Turret Speed", 0);
}

// This method will be called once per scheduler run
void SubTurret::Periodic() {
  _targetX = _limelight->GetNumber("tx", 0.0);
  _targetY = _limelight->GetNumber("ty", 0.0);
  _targetA = _limelight->GetNumber("ta", 0.0);
  _targetVisible = _limelight->GetNumber("tv", 0.0);
  frc::SmartDashboard::PutNumber("Flywheel RPM", GetFlywheelRPM());
  frc::SmartDashboard::PutNumber("Flywheel Current", _spmFlywheelRight.GetOutputCurrent());

  frc::SmartDashboard::PutNumber("Target Angle", GetY());

  frc::SmartDashboard::PutNumber("Turret Angle", GetTurretAngle());
  frc::SmartDashboard::PutNumber("Hood Angle", GetHoodPos());

  frc::SmartDashboard::PutBoolean("Hood Limit", GetHoodLimit());

  //std::cout << _spmTurret.Get() << "   " << _spmTurret.GetOutputCurrent() << "\n";
}

double SubTurret::GetX() {
  return _targetX;
}

double SubTurret::GetY() {
  return _targetY;
}

double SubTurret::GetTargetArea() {
  return _targetA;
}

bool SubTurret::CheckTarget() {
  return _targetVisible;
}

bool SubTurret::GetLeftLimit() {
    return _hlfTurretLeft.Get();
}

bool SubTurret::GetRightLimit() {
    return !_hlfTurretRight.Get();  // Returns true when turret hits limit
}

double SubTurret::GetTurretAngle() {
  return (_encTurret.GetPosition());
}

void SubTurret::ResetTurretEncoder() {
  _encTurret.SetPosition(0);
}

void SubTurret::SetTurret(double speed) {
  _spmTurret.Set(speed);
}

void SubTurret::LimeLEDOn() {
  _limelight->PutNumber("ledMode", 3);
}

void SubTurret::LimeLEDOff() {
  _limelight->PutNumber("ledMode", 1);
}

void SubTurret::SetFlywheel(double speed) {
  _spmFlywheelRight.Set(speed);
}

double SubTurret::GetFlywheelRPM() {
  return _encFlywheel.GetVelocity();
}

void SubTurret::SetHood(double speed) {
  _spmHood.Set(speed);
}

double SubTurret::GetHoodPos() {
  return (_encHood.GetPosition() + _hoodInitialAngle);
}

void SubTurret::ResetHoodEncoder() {
  _encHood.SetPosition(0);
}

bool SubTurret::GetHoodLimit() {
  return _hlfHoodDown.Get();
}

double SubTurret::EstimateDistance() {
  if (!_targetVisible) {
    return 0;
  }
  return ((_targetHeight - _limelightHeight) / (tan(_limelightAngle - GetY())));
}

void SubTurret::SetReady(bool ready) {
  ReadyToShoot = ready;
}

bool SubTurret::IsReady() {
  return ReadyToShoot;
}

double SubTurret::CalculateHoodAngle(double x) {
  return (-0.000008*pow(x,4)) + (0.004*pow(x,3)) - (0.0666*pow(x,2)) + (0.3915*x) + (9.5094);
}