/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <iostream>
#include "frc/Joystick.h"


class OI {
 public:
  OI();
  double getJoystickX();
  double getJoystickY();
 private:
 std::unique_ptr<frc::Joystick> joystick1;

};