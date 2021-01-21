// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Encoder.h>
#include <rev/CANSparkMax.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableInstance.h>
#include <frc/PIDController.h>
#include <frc/DigitalInput.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "Constants.h"


class SubTurret : public frc2::SubsystemBase {
 public:
  SubTurret();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  double GetX();
  double GetY();
  double GetTargetArea();
  bool CheckTarget();
  bool GetLeftLimit();
  double GetTurretAngle();
  void ResetEncoder();

  void SetTurret(double speed);

  void LimeLEDOn();
  void LimeLEDOff();

  void SetFlywheel(double speed);
  double GetFlywheelRPM();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  rev::CANSparkMax _spmTurret{can::spmTurret, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax _spmFlywheelRight{can::spmFlywheelRight, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  frc::Encoder _encTurret{dio::encTurret1, dio::encTurret2};
  frc::DigitalInput _lmtTurretLeft{dio::lmtTurretLeft};

  nt::NetworkTableInstance _networktables;
  std::shared_ptr<nt::NetworkTable> _limelight;

  double _targetX = 0;
  double _targetY = 0;
  double _targetA = 0;
  bool _targetVisible = false;
};
