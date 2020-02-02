/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <iostream>
#include "RobotMap.h"
#include <ctre/Phoenix.h>
#include "frc/commands/Subsystem.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/DoubleSolenoid.h>
#include <frc/DigitalInput.h>

class SubClimber : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  std::unique_ptr<WPI_TalonSRX> srxClimberLeft;
  std::unique_ptr<WPI_TalonSRX> srxClimberRight;

  std::shared_ptr<frc::DoubleSolenoid> SolLock1;
  std::shared_ptr<frc::DoubleSolenoid> SolLock2;

  std::shared_ptr<frc::DigitalInput> LimitClimbUp;
  std::shared_ptr<frc::DigitalInput> LimitClimbDown;

  double _speed = 0.1;
  double _pos;
  double _top = 3222;
  double _dist;

  double _ticksPerMetre = 1000;

  double _targetPosition;

  double kF;

  void configTalon();
 public:
  SubClimber();
  void InitDefaultCommand() override;
  void MoveUp();
  void MoveDown();
  void Stop();
  //void Periodic() override;

  void Lock();
  void Unlock();

  bool LimitClimbUpGet();
  bool LimitClimbDownGet();


  virtual void Periodic();

  int getEncoder();
  double getPos();
  void setSpeed(double speed);
  void ConfigTalon();//default
  void ConfigTalonOverride();//PID off
  void SetPosition(double position);
  double MetresToSensorUnits(double metres);
  double SensorUnitsToMetres(double sensorUnits);
  bool IsOnTarget();
};