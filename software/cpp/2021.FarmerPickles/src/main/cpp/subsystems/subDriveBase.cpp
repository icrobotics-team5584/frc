// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/subDriveBase.h"

subDriveBase::subDriveBase() :
    spxFrontRight{DriveConstants::driveRightFront},
    spxFrontLeft{DriveConstants::driveLeftFront},
    spxBackRight{DriveConstants::driveRightBack},
    spxBackLeft{DriveConstants::driveLeftBack}
    {
        spxFrontRight.ConfigFactoryDefault(50);
        spxFrontLeft.ConfigFactoryDefault(50);
        spxBackRight.ConfigFactoryDefault(50);
        spxBackLeft.ConfigFactoryDefault(50);
    }

// This method will be called once per scheduler run
void subDriveBase::Periodic() {}

void subDriveBase::Drive(double speed, double rotation) {
    DiffDrive.ArcadeDrive(-speed, rotation);
}
