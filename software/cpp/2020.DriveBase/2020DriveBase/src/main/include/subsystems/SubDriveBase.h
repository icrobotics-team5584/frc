/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>

#include "ctre/Phoenix.h"


class SubDriveBase : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

  std::shared_ptr<TalonSRX> _srxFrontLeft;
  std::shared_ptr<TalonSRX> _srxFrontRight;
  std::shared_ptr<TalonSRX> _srxBackLeft;
  std::shared_ptr<TalonSRX> _srxBackRight;

 public:
  SubDriveBase();
  void InitDefaultCommand() override;

  void Drive(double speed, double rotation);

};
