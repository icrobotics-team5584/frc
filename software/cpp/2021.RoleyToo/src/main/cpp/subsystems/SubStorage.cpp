// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubStorage.h"

SubStorage::SubStorage() {
  _spmStorageMotor.SetSmartCurrentLimit(20);
}

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

void SubStorage::ResetEncoder() {
  //TODO: Reset Encoder
}

double SubStorage::GetEncoder() {
  return _spmStorageMotor.GetEncoder().GetPosition();
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

void SubStorage::ScheduleIndexing(bool scheduled) {
  if (scheduled) {
    _needsIndexing = true;
  }
  else {
    _needsIndexing = false;
  }
}

bool SubStorage::NeedsIndexing() {
  return _needsIndexing;
}