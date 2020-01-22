/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


#pragma once

#include <iostream>
#include <frc/Joystick.h>
#include "subsystems/AxisButton.h"

 enum Triggers {
      triggerL = 2,
      triggerR = 3,
};


class OI {
 public:


  OI();
  double getJoystickX();
  double getJoystickY();

  double GetLeftAsix();

 std::unique_ptr<frc::Joystick> joystick1;
 std::unique_ptr<AxisButton> btnSlowDown;

};

