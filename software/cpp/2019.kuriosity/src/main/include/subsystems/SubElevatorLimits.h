#pragma once

#include <frc/WPILib.h>
#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>

using namespace std;
using namespace frc;

class SubElevatorLimits : public frc::Subsystem {
 private:
  
  shared_ptr<DigitalInput> limitTop;
  shared_ptr<DigitalInput> limitBottom;

 public:
  SubElevatorLimits();
  void InitDefaultCommand() override;
  bool GetBottomLimit();
  bool GetTopLimit();
};
