// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "Utilities/PIDk.h"

struct PIDAutoConfig{
  double startX;
  double startY;
  double endX;
  double endY;
  double endHeading;
  double cenX;
  double cenY;
  PIDk PIDconstants;
  double speed;
  double endSpeed;
  PIDk pidSpeed;
};

extern PIDAutoConfig autoRoutineOneLegOne;
extern PIDAutoConfig autoRoutineOneLegTwo;