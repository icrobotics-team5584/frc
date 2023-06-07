// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubIndexer.h"

SubIndexer::SubIndexer() {
};

void SubIndexer::StartIndex() {
    _IndexMotor.Set(0.3);
}

void SubIndexer::StopIndex() {
    _IndexMotor.Set(0);
}


// This method will be called once per scheduler run
void SubIndexer::Periodic() {}
