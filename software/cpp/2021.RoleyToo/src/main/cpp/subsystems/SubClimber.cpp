// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubClimber.h"

SubClimber::SubClimber() {
    _spmClimbLeft.SetInverted(false);
    _spmClimbRight.Follow(_spmClimbLeft, true);
}

// This method will be called once per scheduler run
void SubClimber::Periodic() {}

int SubClimber::GetEncoder(Side side) {
    if (side == Side::left) { return _spmClimbLeft.GetEncoder().GetPosition(); }
    else { return _spmClimbRight.GetEncoder().GetPosition(); }
}

bool SubClimber::GetLimit(Limit limit) {
    switch (limit) {
        case EndStop:
            return _lmtEndStop.Get();
            break;
    } 
}

void SubClimber::Drive(double speed) {
    _spmClimbLeft.Set(speed);
}

//TODO: Encoder PID Drive

void SubClimber::SetPneumatic(Solenoids solenoid, frc::DoubleSolenoid::Value value) {
    switch (solenoid) {
        case Deploy:
            _solClimb.Set(value);
            break;
    }
}