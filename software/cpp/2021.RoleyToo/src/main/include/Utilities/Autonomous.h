// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include <frc/Notifier.h>
#include <frc/Timer.h>
class Autonomous {
 public:
  Autonomous();
  void Periodic();
 private:
  double deletthis =  0;
  const units::second_t fasterPeriod = 19_ms;
  frc::Notifier notifier{ [this]{Periodic();} };
  frc::Timer timer;
};
