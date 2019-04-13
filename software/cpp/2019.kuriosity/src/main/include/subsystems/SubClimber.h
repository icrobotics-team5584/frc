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
  shared_ptr<VictorSPX> _spxClimber;
  shared_ptr<VictorSPX> _spxClimberSlave;
  shared_ptr<Servo> _srvLatch;
  shared_ptr<DigitalInput> _limLimit;

  const double LATCHED_POSITION = 0.5;
  const double UNLATCHED_POSITION = 0;
  const double IS_LATCHED_TOLERANCE = 0.1;
  const double HOLD_POWER = 0.17;
  const double LIFT_POWER = 0.8;
  const double RETRACT_POWER = -0.25;
  const double STORE_POWER = -0.06; // 1 Volt desiredvoltage/currentvoltage

 public:
  SubClimber();
  void InitDefaultCommand() override;
  void Go();
  void Retract();
  void Stop();
  void Hold();
  void Latch();
  void Unlatch();
  bool IsLatched();
  bool GetLimit();
};
