/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include <pidControllers/PidoutRoller.h>
#include <pidControllers/PidsrcRoller.h>

enum RollerPosition {OUT, UP, IN};

class SubRollerIntakeBar : public frc::Subsystem {
friend class PidoutRoller;
 public:
  SubRollerIntakeBar();
  void InitDefaultCommand() override;
  void SetPIDEnabled(bool enabled);
  void SetSetpoint(double angle);
  void SetSetpoint(RollerPosition rollerPosition);
  double GetAngle();
  bool OnTarget();

 private:
  const double SENSOR_UNITS_OUT = 1007;
  const double SENSOR_UNITS_IN = -743;
  const double DEGREES_OUT = 173;
  const double SENSOR_UNITS_PER_DEGREE = (SENSOR_UNITS_OUT - SENSOR_UNITS_IN) / DEGREES_OUT;
  void MoveBar(double power);
  std::shared_ptr<WPI_TalonSRX> srxRollerBar;
  std::unique_ptr<frc::PIDController> positionController;
  std::unique_ptr<PidsrcRoller> pidsrcRoller;
  std::unique_ptr<PidoutRoller> pidoutRoller;
};
