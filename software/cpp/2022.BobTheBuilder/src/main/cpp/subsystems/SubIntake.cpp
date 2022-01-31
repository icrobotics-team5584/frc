// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubIntake.h"

SubIntake::SubIntake() = default;

// This method will be called once per scheduler run
void SubIntake::Periodic() {

}
void SubIntake::Intake(){
  _spmIntake.Set(1);
}

void SubIntake::Outtake() {
  _spmIntake.Set(-1);
}


void SubIntake::Extend() {
  _solPnuematics.Set(frc::DoubleSolenoid::Value::kForward);
}
void SubIntake::Retract() {
  _solPnuematics.Set(frc::DoubleSolenoid::Value::kReverse);
}

