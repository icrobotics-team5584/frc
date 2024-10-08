// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <frc/DoubleSolenoid.h>
#include "Constants.h"

class SubIntake : public frc2::SubsystemBase {
 public:
  SubIntake();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void Intake();
  void Outtake();
  void Extend();
  void Retract();
  void Stop();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  rev::CANSparkMax _spmIntake{can::spmIntake, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
   frc::DoubleSolenoid _solPnuematics{1,frc::PneumaticsModuleType::CTREPCM,pcm::solIntakeOut,pcm::solIntakeIn};
};