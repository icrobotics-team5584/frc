/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/WPILib.h>
#pragma once

class OI {
 public:
  OI();
  double GetJoystickX();
  double GetJoystickY();
  std::unique_ptr<frc::JoystickButton> btnAutoTurn;
  frc::Joystick joystick1;
  std::unique_ptr<frc::JoystickButton> btnAutoDrive;

};
