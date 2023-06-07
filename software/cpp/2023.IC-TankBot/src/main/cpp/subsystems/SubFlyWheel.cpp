// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubFlyWheel.h"

SubFlyWheel::SubFlyWheel(){

}

void SubFlyWheel::StartFlyWheel() {
    _FlyWheelMotor.Set(0.3);
}

void SubFlyWheel::StopFlyWheel() {
    _FlyWheelMotor.Set(0);
}



// This method will be called once per scheduler run
void SubFlyWheel::Periodic() {}

