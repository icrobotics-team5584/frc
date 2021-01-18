// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubIntake.h"
#include <frc/smartdashboard/SmartDashboard.h>

SubIntake::SubIntake(){
    frc::SmartDashboard::PutData("Intake Motor", &_spmIntake);
}

// This method will be called once per scheduler run
void SubIntake::Periodic() {

}

void SubIntake::Intake(){
    _spmIntake.Set(kSpeed);
}

void SubIntake::Outtake(){
    _spmIntake.Set(-kSpeed);
}

void SubIntake::Deploy(){
    solIntake.Set(frc::DoubleSolenoid::kForward);
}

void SubIntake::Retract(){
    solIntake.Set(frc::DoubleSolenoid::kReverse);
}



