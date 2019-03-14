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
using namespace frc;

class SubClimber : public frc::Subsystem {
 private:
   // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  shared_ptr<WPI_TalonSRX> _srxClimber;
  shared_ptr<Servo> _srvLatch;
  const double LATCHED_POSITION = 0.25;
  const double UNLATCHED_POSITION = 0;
  const double IS_LATCHED_TOLERANCE = 0.1;

 public:
  SubClimber();
  void InitDefaultCommand() override;
  void Go();
  void Stop();
  void Latch();
  void Unlatch();
  bool IsLatched();
};
