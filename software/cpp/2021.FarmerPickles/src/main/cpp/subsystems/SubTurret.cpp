// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubTurret.h"

SubTurret::SubTurret() :
    _turretEncoder{TurretConstants::turretEncoderPin1,TurretConstants::turretEncoderPin2}
    {
        _turretEncoder.SetDistancePerPulse(360./8192.); // Convert encoder ticks to degrees
        _turretEncoder.SetMaxPeriod(.1);
    }

// This method will be called once per scheduler run
void SubTurret::Periodic() {}

double SubTurret::getTurretAngle() {
    return _turretEncoder.GetDistance();
}

double SubTurret::getTurretRate() {
    return _turretEncoder.GetRate();
}

bool SubTurret::getTurretStopped() {
    return _turretEncoder.GetStopped();
}
bool SubTurret::getTurretDirection() {
    return _turretEncoder.GetDirection();
}