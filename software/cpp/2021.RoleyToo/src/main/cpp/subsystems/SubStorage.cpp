// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubStorage.h"

SubStorage::SubStorage() = default;

// This method will be called once per scheduler run
void SubStorage::Periodic() {}

void SubStorage::Move(Direction direction, double speed) {
  switch (direction) {
    case Forward:
      _spmStorageMotor.Set(speed);
      break;
    case Backward:
      _spmStorageMotor.Set(-speed);
      break;
  }
}

double SubStorage::GetEncoder() {
  return _spmStorageMotor.Get();
}

bool SubStorage::GetSensor(Sensors sensor) {
  switch (sensor) {
    case Intake:
      return _brkIntake.Get();
      break;
    
    case Index:
      return _brkIndex.Get();
      break;

    case Outtake:
      return _brkOuttake.Get();
      break;
    }

  return false; //Make the compiler happy in case none of these choices are made
}

int SubStorage::GetBallCount() {
  return _ballCount;
}

void SubStorage::SetBallCount(int ballCount) {
  _ballCount = ballCount;
}