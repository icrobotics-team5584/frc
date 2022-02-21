// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <frc/DigitalInput.h>
#include <frc/DoubleSolenoid.h>
#include "Constants.h"

class SubClimber : public frc2::SubsystemBase {
 public:
  SubClimber();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void Extend();
  void Retract();
  void Rotate();
  void Stow();
  bool IsTopPressed();
  bool IsBottomPressed();
  void ResetEncoder();
 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  rev::CANSparkMax _spmLeftElevator{can::spmLeftClimber, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax _spmRightElevator{can::spmRightClimber, rev::CANSparkMax::MotorType::kBrushless};
  frc::DoubleSolenoid _solTilter{1, frc::PneumaticsModuleType::CTREPCM,pcm::solClimbTilterForward,pcm::solClimbTilterReverse};
  frc::DigitalInput _lmtTop{dio::lmtClimberTop};
  frc::DigitalInput _lmtBottom{dio::lmtClimberBottom};
  rev::SparkMaxRelativeEncoder _encLeftElevator{_spmLeftElevator.GetEncoder()};
  rev::SparkMaxRelativeEncoder _encRightElevator{_spmRightElevator.GetEncoder()};
  rev::SparkMaxPIDController _pidLeftMotorController = _spmLeftElevator.GetPIDController();
  rev::SparkMaxPIDController _pidRightMotorController = _spmRightElevator.GetPIDController();

};
