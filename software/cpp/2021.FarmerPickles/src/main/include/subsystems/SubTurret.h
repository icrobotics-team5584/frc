// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Encoder.h>
#include <rev/CANSparkMax.h>

#include "Constants.h"

class SubTurret : public frc2::SubsystemBase {
 public:
  SubTurret();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  double getTurretAngle();
  double getTurretRate();
  bool getTurretStopped();
  bool getTurretDirection();

  double targetX;
  double targetY;




 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  frc::Encoder _turretEncoder;
};
