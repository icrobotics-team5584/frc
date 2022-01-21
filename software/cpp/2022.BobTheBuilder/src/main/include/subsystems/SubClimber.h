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
 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  rev::CANSparkMax _spmElevator{can::spmClimber, rev::CANSparkMax::MotorType::kBrushless};
  frc::DoubleSolenoid _solTilter{frc::PneumaticsModuleType::CTREPCM,pcm::solTilterForward,pcm::solTilterReverse};
  frc::DigitalInput _lmtTop{dio::lmtClimberTop};
  frc::DigitalInput _lmtBottom{dio::lmtClimberBottom};
};
