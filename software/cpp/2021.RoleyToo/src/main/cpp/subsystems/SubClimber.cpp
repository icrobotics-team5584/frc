// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubClimber.h"

SubClimber::SubClimber() {
    _spmClimbLeft.RestoreFactoryDefaults();
    _spmClimbRight.RestoreFactoryDefaults();

    _leftEncoder.SetPosition(0);
    _rightEncoder.SetPosition(0);

    _spmClimbLeft.SetSmartCurrentLimit(30);
    _spmClimbRight.SetSmartCurrentLimit(30);
}

// This method will be called once per scheduler run
void SubClimber::Periodic() {}

int SubClimber::GetEncoder(Side side) {
    if (side == Side::left) { return _leftEncoder.GetPosition(); }
    else { return _rightEncoder.GetPosition(); }
}

bool SubClimber::GetLimit(Limit limit) {
    switch (limit) {
        case EndStop:
            return _lmtEndStop.Get();
            break;
    } 
    return false;
}

void SubClimber::Retract(double speed, Side side) {
    switch (side) {
        case left:
            _spmClimbLeft.Set(speed);
            break;
        case right:
            _spmClimbRight.Set(speed);
            break;
    }
}

//TODO: Encoder PID Drive

void SubClimber::SetPneumatic(Solenoids solenoid, frc::DoubleSolenoid::Value value) {
    switch (solenoid) {
        case Deploy:
            _solClimb.Set(value);
            break;
    }
}

void SubClimber::SetMode(bool mode) {
    if (mode) {
        _spmClimbLeft.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
        _spmClimbRight.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    }
    else {
        _spmClimbLeft.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
        _spmClimbRight.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    }
}