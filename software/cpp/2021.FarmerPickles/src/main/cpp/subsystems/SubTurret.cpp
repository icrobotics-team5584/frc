// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubTurret.h"


SubTurret::SubTurret() :
    _turretEncoder{TurretConstants::turretEncoderPin1, TurretConstants::turretEncoderPin2},
    _spmTurret{8}         // CHANGE TO BRUSHLESS ON ACTUAL ROBOT
    {
        //_turretEncoder.SetDistancePerPulse(360./2048.); // Convert encoder ticks to degrees
        _networktables = nt::NetworkTableInstance::GetDefault();
        _limelight = _networktables.GetTable("limelight");

        frc::SmartDashboard::PutNumber("turretP", 0.2);
        frc::SmartDashboard::PutNumber("turretI", 0);
        frc::SmartDashboard::PutNumber("turretD", 0);

    }

// This method will be called once per scheduler run
void SubTurret::Periodic() {
    targetX = _limelight->GetNumber("tx", 0.0);
    targetY = _limelight->GetNumber("ty", 0.0);
    targetA = _limelight->GetNumber("ta", 0.0);
    targetVisible = _limelight->GetNumber("tv", 0.0);

    frc::SmartDashboard::GetNumber("turretP", 0.2);
    frc::SmartDashboard::GetNumber("turretI", 0);
    frc::SmartDashboard::GetNumber("turredD", 0);

    _spmTurret.Set(turretPID.Calculate(targetX));


}

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

void SubTurret::turnTurret(double speed) {
    _spmTurret.Set(speed);
}

void SubTurret::stopTurret() {
    _spmTurret.StopMotor();
}

void SubTurret::limeLEDState(bool state) {
    if (state) {
        _limelight->PutNumber("ledMode", 3);
    }
    else
    {
        _limelight->PutNumber("ledMode", 1);
    }
    
}