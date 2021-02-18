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
  DriveInput autoDrive(double startX, double startY, double endX, double endY, double endHeading, double cenX, double cenY);
 private:
  const units::second_t fasterPeriod = 10_ms;
  const double pi = 3.1415926535897932384626433832795028841971693993751;
  double posX;
  double posY;
  double dollyPosX;
  double dollyPosY;
  double angleOffset;
  double prevDistance;
  double kP = 3.25;
  double kI = 0.00;
  double kD = 20;
  const double speed = -0.1;
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
  double leftRight; //
  const double metersToFront = 0.4;
  const double metersToBack = 0.45;
  double pidReverse = 0;
  DriveInput autoOutput;
  frc::Notifier notifier{ [this]{Periodic();} };
  std::function<double()> _getYaw;
  std::function<double()> _getDistance;
};
