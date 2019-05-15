#pragma once

#include <frc/WPILib.h>

class PidoutRoller : public frc::PIDOutput {
 public:
  PidoutRoller();
  void PIDWrite(double output);
};
