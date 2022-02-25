// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/DoubleSolenoid.h>
#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>

#include "Constants.h"

class SubStorage : public frc2::SubsystemBase {
 public:
  SubStorage();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void In();
  void Stop();
  void Out();
  void ExtendStopper();
  void RetractStopper();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  rev::CANSparkMax _spmStorage{can::spmStorage,
                               rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  frc::DoubleSolenoid _solStopper{1, frc::PneumaticsModuleType::CTREPCM, pcm::solStorageStopperForward, pcm::solStorageStopperReverse};

};
