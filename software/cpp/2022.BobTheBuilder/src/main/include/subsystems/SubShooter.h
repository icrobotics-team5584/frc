// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <frc/DoubleSolenoid.h>

#include "Constants.h"

class SubShooter : public frc2::SubsystemBase {
 public:
  SubShooter();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void Shoot();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  rev::CANSparkMax _spmShooter1{5, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax _spmShooter2{6, rev::CANSparkMaxLowLevel::MotorType::kBrushless};

};
