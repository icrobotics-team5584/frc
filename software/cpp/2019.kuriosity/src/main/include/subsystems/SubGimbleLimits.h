#pragma once

#include <frc/WPILib.h>
#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <iostream>

using namespace std;
using namespace frc;

class SubGimbleLimits : public frc::Subsystem {
 private:
  
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
