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
  std::unique_ptr<frc::JoystickButton> btnArmPid;
  std::unique_ptr<frc::JoystickButton> btnInspireArm;

  std::unique_ptr<frc::JoystickButton> btnArmForward;
  std::unique_ptr<frc::JoystickButton> btnArmBackwards;

  std::unique_ptr<frc::JoystickButton> btnArmToFloor;
  std::unique_ptr<frc::JoystickButton> btnArmToHab;
  std::unique_ptr<frc::JoystickButton> btnArmToHatch;
  std::unique_ptr<frc::JoystickButton> btnArmToSky;
  std::unique_ptr<frc::JoystickButton> btnArmToPreHab;

  std::unique_ptr<frc::JoystickButton> btnClimber;
};
