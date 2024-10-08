// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include "Constants.h"
#include <frc/DigitalInput.h>

class SubStorage : public frc2::SubsystemBase {
 public:
  SubStorage();

  enum Sensors {
    Intake = 1,
    Index = 2,
    Outtake = 3
  };

  enum Direction {
    Forward = 0,
    Backward = 1
  };

  void Move(Direction direction, double speed);
  void MoveFeeder(Direction direction, double speed);
  double GetEncoder();
  double GetEncoderSpeed();
  double GetStorageCurrent();
  void ResetEncoder();
  void SetBallCount(int ballCount);
  int GetBallCount();
  bool GetSensor(Sensors sensor);
  bool NeedsIndexing();
  void ScheduleIndexing(bool scheduled);
  void Feed(double speed);

  int GetDirection();
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  rev::CANSparkMax _spmStorageMotor{can::spmStorage, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax _spmFeederMotor{can::spmFeeder, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANEncoder _encStorageMotor{_spmStorageMotor.GetEncoder()};
  frc::DigitalInput _brkIntake{dio::brkStorageIn};
  frc::DigitalInput _brkIndex{dio::brkStorageIndex};
  frc::DigitalInput _brkOuttake{dio::brkStorageOut};
  int _ballCount;
  bool _needsIndexing = false;
  int _currentDirection = 0;
};
