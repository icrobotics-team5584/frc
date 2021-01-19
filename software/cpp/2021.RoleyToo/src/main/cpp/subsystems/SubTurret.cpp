// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubTurret.h"

SubTurret::SubTurret() :
    _spmTurret{can::spmTurret, rev::CANSparkMaxLowLevel::MotorType::kBrushless},
    _encTurret{dio::encTurret1, dio::encTurret2},
    _lmtTurretLeft{dio::lmtTurretLeft}
    {
        _encTurret.SetDistancePerPulse(360.0/2048.0);
        _networktables = nt::NetworkTableInstance::GetDefault();
        _limelight = _networktables.GetTable("limelight");
    }

// This method will be called once per scheduler run
void SubTurret::Periodic() {
    targetX = _limelight->GetNumber("tx", 0.0);
    targetY = _limelight->GetNumber("ty", 0.0);
    targetA = _limelight->GetNumber("ta", 0.0);
    targetVisible = _limelight->GetNumber("tv", 0.0);
}

double SubTurret::GetX() {
    return targetX;
}

double SubTurret::GetY() {
    return targetY;
}

double SubTurret::GetTargetArea() {
    return targetA;
}

bool SubTurret::CheckTarget() {
    return targetVisible;
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

void SubTurret::LimeLEDState(bool state) {
    if (state) {
        _limelight->PutNumber("ledMode", 3);
    }
    else
    {
        _limelight->PutNumber("ledMode", 1);
    }
}