/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/WPILib.h>
#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>

using namespace std;
class SubRollerIntake : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  shared_ptr<WPI_TalonSRX> _srxRoller;
  double inSpeed = 1.0;
  double outSpeed = -1.0;
 public:
  SubRollerIntake();
  void RollerIn();
  void RollerOut();
  void Stop();
  void InitDefaultCommand() override;
};
