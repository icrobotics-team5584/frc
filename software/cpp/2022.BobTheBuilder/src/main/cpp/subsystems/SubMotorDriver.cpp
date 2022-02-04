// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubMotorDriver.h"

SubMotorDriver::SubMotorDriver() {
    
}

// This method will be called once per scheduler run
void SubMotorDriver::Periodic() {}

void SubMotorDriver::Drive(double _output) {
    _motor.Set(_output);
    std::cout << "Setting Drive output to " << _output << std::endl;
}