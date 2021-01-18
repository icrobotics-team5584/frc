// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/ColorSensorV3.h>

class SubColorWheel : public frc2::SubsystemBase {
 public:
  SubColorWheel();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
  rev::ColorSensorV3 _colorSensor{frc::I2C::Port::kOnboard};
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
