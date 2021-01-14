// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubIntake.h"

SubIntake::SubIntake(){

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



