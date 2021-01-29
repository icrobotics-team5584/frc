// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubStorage.h"

SubStorage::SubStorage() = default;

// This method will be called once per scheduler run
void SubStorage::Periodic() {}

void SubStorage::Move(bool direction, double speed) {
    
  if (direction) {
    _spmStorageMotor.Set(speed);
  }
  else {
    _spmStorageMotor.Set(-speed);
  }
}

double SubStorage::GetEncoder() {
  return _spmStorageMotor.Get();
}

bool SubStorage::GetSensor(Sensors sensor) {
  switch (sensor) { //TODO: Add sensors to subsystem and get() here.
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