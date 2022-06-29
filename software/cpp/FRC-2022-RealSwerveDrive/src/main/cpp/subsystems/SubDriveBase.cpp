// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubDriveBase.h"
#include <frc/smartdashboard/SmartDashboard.h>

SubDriveBase::SubDriveBase() {
    frc::SmartDashboard::PutNumber("Target_Degrees", 0);
};

// This method will be called once per scheduler run
void SubDriveBase::Periodic() {
    auto _state = swerveModule.GetState();
    _state.angle = frc::Rotation2d(units::degree_t(frc::SmartDashboard::GetNumber("Target_Degrees", 0)));
    swerveModule.SetDesiredState(_state);
}

