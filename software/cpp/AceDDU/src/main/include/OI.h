/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/WPILib.h>
#include "../include/commands/cmdArmPos0.h"
#pragma once

class OI {
 public:
  OI();
  double GetJoystickX();
  double GetJoystickY();
  std::shared_ptr<frc::Joystick> joystick1;

  std::shared_ptr<frc::JoystickButton> btnArm0;
  std::shared_ptr<frc::JoystickButton> btnArm45;
  std::shared_ptr<frc::JoystickButton> btnArm90;
  std::shared_ptr<frc::JoystickButton> btnArm180;
};
