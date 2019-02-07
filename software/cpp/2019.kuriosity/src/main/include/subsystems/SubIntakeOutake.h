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
class SubIntakeOutake : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  shared_ptr<WPI_TalonSRX> _srxIntakeOutake;
  shared_ptr<frc::DigitalInput> _dinCargoLimit;
  double outSpeed = -0.8;
  double inSpeed = 1;

 public:
  SubIntakeOutake();
  void InitDefaultCommand() override;
  void Intake();
  void Outake();
  void Stop();
  bool GetCargoLimitSwitch();
};
