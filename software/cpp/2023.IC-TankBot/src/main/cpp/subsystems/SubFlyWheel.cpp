// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubFlyWheel.h"
#include <frc/smartdashboard/SmartDashboard.h>

SubFlyWheel::SubFlyWheel(){
    frc::SmartDashboard::PutNumber("Flywheel", 0.1);
}

void SubFlyWheel::StartFlyWheel() {
    _FlyWheelMotor.Set(frc::SmartDashboard::GetNumber("Flywheel", 0));
}

void SubFlyWheel::StopFlyWheel() {
    _FlyWheelMotor.Set(0);
}



// This method will be called once per scheduler run
void SubFlyWheel::Periodic() {}

