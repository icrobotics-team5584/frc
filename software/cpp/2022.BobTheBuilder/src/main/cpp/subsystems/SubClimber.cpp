// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubClimber.h"

SubClimber::SubClimber() = default;

// This method will be called once per scheduler run
void SubClimber::Periodic() {}
void SubClimber::Extend() {
  _spmElevator.Set(.4);
}

void SubClimber::Retract() {
  _spmElevator.Set(-.4);
}

void SubClimber::Rotate() {
_solTilter.Set(frc::DoubleSolenoid::kForward);
}

void SubClimber::Stow() {
  _solTilter.Set(frc::DoubleSolenoid::kReverse);
}

bool SubClimber::IsTopPressed() {
  return _lmtTop.Get();
}
bool SubClimber::IsBottomPressed() {
  return _lmtBottom.Get();
}