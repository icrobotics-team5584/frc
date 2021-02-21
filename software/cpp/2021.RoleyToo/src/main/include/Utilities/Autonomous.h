// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include <frc/Notifier.h>
#include "Utilities/PIDk.h"
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
  DriveInput autoDrive(double startX, double startY, double endX, double endY, double endHeading, double cenX, double cenY, PIDk PIDk, double speed);
 private:
  const units::second_t fasterPeriod = 10_ms;
  const double pi = 3.1415926535897932384626433832795028841971693993751;
  double posX;
  double posY;
  double dollyPosX;
  double dollyPosY;
  double angleOffset;
  double prevDistance;
  double error;
  double steering;
  double intergral;
  double previousError = 0;
  double cenX;
  double cenY;
  double radius;
  double slope;
  bool isLinear;
  double frontPosX;
  double frontPosY;
  double backPosX;
  double backPosY;
  const double metersToFront = 0.4;
  const double metersToBack = 0.45;
  DriveInput autoOutput;
  frc::Notifier notifier{ [this]{Periodic();} };
  std::function<double()> _getYaw;
  std::function<double()> _getDistance;
};
