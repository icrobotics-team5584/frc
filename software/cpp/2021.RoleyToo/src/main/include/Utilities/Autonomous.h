// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include <frc/Notifier.h>

struct DriveInput {
    double steering;
    double speed;
};

class Autonomous {
 public:
  Autonomous(std::function<double()> getYaw, std::function<double()> getDistance);
  void Periodic();
  void updatePosition();
  void setPosition(double x, double y);
  void setAngle(double theta);
  DriveInput autoDrive(double x, double y, double radius);
 private:
  const units::second_t fasterPeriod = 10_ms;
  double posX;
  double posY;
  double angleOffset;
  double prevDistance;
  double kP = -2;
  double kI = 0.00;
  double kD = -150;
  double speed = 0.1;
  double error;
  double steering;
  double intergral;
  double previousError = 0;
  DriveInput autoOutput;
  frc::Notifier notifier{ [this]{Periodic();} };
  std::function<double()> _getYaw;
  std::function<double()> _getDistance;
};
