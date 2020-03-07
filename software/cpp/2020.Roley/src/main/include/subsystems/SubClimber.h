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
#include <frc/Timer.h>

class SubClimber : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  std::unique_ptr<WPI_TalonSRX> srxClimberLeft;
  std::unique_ptr<WPI_TalonSRX> srxClimberRight;

  std::shared_ptr<frc::DoubleSolenoid> solClimberRatchets;

  std::shared_ptr<frc::DigitalInput> LimitClimbUp;
  std::shared_ptr<frc::DigitalInput> LimitClimbDown;

  double _upSpeed = 0.1;
  double _downSpeed = 0.5;
  double _pos;
  double _top = 3222;
  double _dist;

  double _ticksPerMetre = 1000;

  double _targetPosition;

  double kF;

  bool isElevatorLocked = true;

  void configTalon();

  frc::Timer timer;

  double error;
  double target = 0;
  double intergral;
  double derivative;
  double lastError = 0;
  double PIDOutput;
  double kP = -0.0008;
  double kI = 0;
  double kD = 0;
  double maxUpSpeed = 0.9;
  double maxDownSpeed = -0.8;

  double buddyTarget = 3634;

  bool startedDown;
  bool PIDEnabled = true;

 public:
  SubClimber();
  void InitDefaultCommand() override;
  void MoveUp();
  void MoveDown();
  void Stop();
  //void Periodic() override;

  void RatchetsDisengage();
  void RatchetsEngage();

  void ElevatorPID();

  bool LimitClimbUpGet();
  bool LimitClimbDownGet();


  virtual void Periodic();

  int getEncoder();
  double getPos();
  void setSpeed(double speed);
  void SetPosition(double position);
  double MetresToSensorUnits(double metres);
  double SensorUnitsToMetres(double sensorUnits);
  bool IsOnTarget();
  void CustomPID(double PIDIntput);
  void ElevatorExtendMax();
  void ElevaterExtendMin();
  void ElevatorExtendBuddy();
  void EnablePID();
  void DisablePID();
  bool IsAtTarget();
};
