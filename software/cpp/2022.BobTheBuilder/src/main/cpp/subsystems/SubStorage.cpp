// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubStorage.h"

SubStorage::SubStorage() = default;

// This method will be called once per scheduler run
void SubStorage::Periodic() {}

void SubStorage::In() {
    _spmStorage.Set(0.4);
}