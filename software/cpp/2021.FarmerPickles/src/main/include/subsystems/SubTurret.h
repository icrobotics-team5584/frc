// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Encoder.h>
#include <rev/CANSparkMax.h>
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"

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

  void turnTurret(double speed);
  void stopTurret();

  void limeLEDState(bool state);

  double targetX = 0;
  double targetY = 0;
  double targetA = 0;
  bool targetVisible = false;






 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  frc::Encoder _turretEncoder;
  rev::CANSparkMax _spmTurret;
  nt::NetworkTable _limelight;
};