// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include <frc/Notifier.h>

class Autonomous {
 public:
  Autonomous();
  void Periodic();
 private:
  const units::second_t fasterPeriod = 19_ms;
  frc::Notifier notifier{ [this]{Periodic();} };
};
