// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Encoder.h>
#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h>
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"
#include <frc/controller/PIDController.h>
#include "Constants.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "frc/DigitalInput.h"

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

  double GetX();
  double GetY();
  double GetTargetArea();
  bool CheckTarget();
  bool GetSwitch();
  bool GetLinebreak();

  void setTurret(double speed);
  void stopTurret();

  void limeLEDState(bool state);

  void ResetEncoder();


  void SetFlywheel(double speed);
  double GetFlywheelVelocity();





 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  bool _turretHomed = false;
  bool _inStartingPos = false;
  frc::Encoder _turretEncoder;
  frc::DigitalInput _limitSwitch;
  frc::DigitalInput _linebreak;
  WPI_TalonSRX _spmTurret;
  rev::CANSparkMax _spmFlywheel;


  nt::NetworkTableInstance _networktables;
  std::shared_ptr<nt::NetworkTable> _limelight;

  double targetX = 0;
  double targetY = 0;
  double targetA = 0;
  bool targetVisible = false;


};