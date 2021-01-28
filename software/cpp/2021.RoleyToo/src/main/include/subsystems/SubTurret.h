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
  bool GetRightLimit();
  double GetTurretAngle();
  void ResetTurretEncoder();

  void SetTurret(double speed);
  double EstimateDistance();

  void LimeLEDOn();
  void LimeLEDOff();

  void SetFlywheel(double speed);
  double GetFlywheelRPM();

  void SetHood(double speed);
  double GetHoodPos();
  

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  rev::CANSparkMax _spmTurret{can::spmTurret, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax _spmFlywheelRight{can::spmFlywheelRight, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax _spmFlywheelLeft{can::spmFlywheelLeft, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax _spmHood{can::spmHood, rev::CANSparkMaxLowLevel::MotorType::kBrushless};

  rev::CANEncoder _encTurret;

  //frc::Encoder _encTurret{dio::encTurret1, dio::encTurret2};
  frc::Encoder _encHood{dio::encHood1, dio::encHood2};

  frc::DigitalInput _hlfTurretLeft{dio::hlfTurretLeft};
  frc::DigitalInput _hlfTurretRight{dio::hlfTurretRight};
  frc::DigitalInput _hlfHoodDown{dio::hlfHoodDown};

  nt::NetworkTableInstance _networktables;
  std::shared_ptr<nt::NetworkTable> _limelight;

  double _targetX = 0;
  double _targetY = 0;
  double _targetA = 0;
  bool _targetVisible = false;

  double _targetHeight = 1300;
  double _limelightHeight = 260;
  double _limelightAngle = 40;
  double _encTurretConvFac = 360/1;    // 360 points per 1 revolution
};
