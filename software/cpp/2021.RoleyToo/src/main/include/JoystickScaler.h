/*
 * JoystickScaler.h
 *
 *  Created on: 26 Jan. 2021
 *      Author: Mitch
 */

#pragma once

#include "frc/Joystick.h"
#include <iostream>

class JoystickScaler :
public frc::Joystick{
 public:
  JoystickScaler(int deviceID, double scaleLeft, double scaleRight);
  double GetScaledX(frc::GenericHID::JoystickHand hand);
  double GetScaledY(frc::GenericHID::JoystickHand hand);
 private:
 double _scaleLeft;
 double _scaleRight;
 double _scale;
};
