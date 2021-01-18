// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include <frc/Notifier.h>
#include <string>
class Autonomous {
 public:
  Autonomous(std::function<double()> getYaw, std::function<double()> getDistance);
  void Periodic();
  void updatePosition();
  void setPosition(double x, double y);
  void setAngle(double theta);
  void autoDrive(std::string curve);
 private:
  const units::second_t fasterPeriod = 10_ms;
  double posX;
  double posY;
  double angleOffset;
  double prevDistance;
  frc::Notifier notifier{ [this]{Periodic();} };
  std::function<double()> _getYaw;
  std::function<double()> _getDistance;
};
