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

int SubClimber::GetEncoder(bool side) {
    if (side) { return _spmClimbLeft.GetEncoder().GetPosition(); }
    else { return _spmClimbRight.GetEncoder().GetPosition(); }
}

void SubClimber::Drive(double speed) {
    _spmClimbLeft.Set(speed);
}

void SubClimber::SetPneumatic(frc::DoubleSolenoid::Value value) {
    _solClimb.Set(value);
}