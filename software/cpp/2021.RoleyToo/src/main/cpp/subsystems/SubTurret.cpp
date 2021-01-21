// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubTurret.h"

SubTurret::SubTurret()
    {
        _encTurret.SetDistancePerPulse(360.0/2048.0);
        _networktables = nt::NetworkTableInstance::GetDefault();
        _limelight = _networktables.GetTable("limelight");
        LimeLEDOff();

    }

// This method will be called once per scheduler run
void SubTurret::Periodic() {
    _targetX = _limelight->GetNumber("tx", 0.0);
    _targetY = _limelight->GetNumber("ty", 0.0);
    _targetA = _limelight->GetNumber("ta", 0.0);
    _targetVisible = _limelight->GetNumber("tv", 0.0);
    frc::SmartDashboard::PutNumber("Flywheel RPM", GetFlywheelRPM());
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
    return _lmtTurretLeft.Get();
}

double SubTurret::GetTurretAngle() {
    return _encTurret.GetDistance();
}

void SubTurret::ResetEncoder() {
    _encTurret.Reset();
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
    return _spmFlywheelRight.GetEncoder().GetVelocity();
}