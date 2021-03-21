// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubIntake.h"
#include <frc/smartdashboard/SmartDashboard.h>

SubIntake::SubIntake(){
    frc::SmartDashboard::PutData("Intake Motor", &_spmIntake);

    _spmIntake.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    _spmIntake.SetSmartCurrentLimit(20);
    solIntake.Set(frc::DoubleSolenoid::kReverse);
}

// This method will be called once per scheduler run
void SubIntake::Periodic() {

}

void SubIntake::Intake(){
    _spmIntake.Set(kSpeed);
}

void SubIntake::Intake(double speed){
    _spmIntake.Set(speed);
}

void SubIntake::Outtake(){
    _spmIntake.Set(-kSpeed);
}

void SubIntake::Stop() {
    _spmIntake.Set(0);
}

void SubIntake::Deploy(){
    solIntake.Set(frc::DoubleSolenoid::kForward);
}

void SubIntake::Retract(){
    solIntake.Set(frc::DoubleSolenoid::kReverse);
}



