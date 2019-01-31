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
#include <iostream>

using namespace std;
using namespace frc;

class SubGimbleLimits : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

    shared_ptr<DigitalInput> limitLeft;
    shared_ptr<DigitalInput> limitRight;

    int outCount = 0;

 public:
  SubGimbleLimits();
  void InitDefaultCommand() override;
  void Periodic();
  bool GetLeftLimit();
  bool GetRightLimit();
  bool GetBothLimits();
};
