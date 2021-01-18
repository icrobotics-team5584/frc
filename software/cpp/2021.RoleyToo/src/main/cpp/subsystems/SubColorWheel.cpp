// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubColorWheel.h"
#include <frc/smartdashboard/smartdashboard.h>

SubColorWheel::SubColorWheel() = default;

// This method will be called once per scheduler run
void SubColorWheel::Periodic() {
    frc::Color detectedColor = _colorSensor.GetColor();
    frc::SmartDashboard::PutNumber("Red", detectedColor.red);
    frc::SmartDashboard::PutNumber("Green", detectedColor.green);
    frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);
}
