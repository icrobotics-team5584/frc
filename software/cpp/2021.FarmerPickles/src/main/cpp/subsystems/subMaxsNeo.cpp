// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/subMaxsNeo.h"

#include <frc/smartdashboard/SmartDashboard.h>

subMaxsNeo::subMaxsNeo() : 
    driveMotor{TestConstants::testMotorPort, rev::CANSparkMaxLowLevel::MotorType::kBrushless}
{
    //frc::SmartDashboard::PutData()
}

// This method will be called once per scheduler run
void subMaxsNeo::Periodic() {}

void subMaxsNeo::driveMaxsNeo(int percentage) {
    driveMotor.Set(percentage);
}