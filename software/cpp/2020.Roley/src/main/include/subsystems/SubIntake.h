/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include "RobotMap.h"
#include "ctre/Phoenix.h"

class SubIntake : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  const double kDefaultSpeed = 0.6;
  double _speed = kDefaultSpeed;
  std::shared_ptr<TalonSRX> srxIntake;

 public:
  SubIntake();
  void InitDefaultCommand() override;
  void Intake();
  void Outtake();
  void Stop();
  virtual void Periodic();
};
