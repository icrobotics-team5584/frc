/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/WPILib.h>
#include "../include/commands/cmdArmPos0.h"
#include "customButtons/ButtonPOV.h"
#include "customButtons/ToggleButton.h"

#pragma once

enum Buttons{
      aBtn = 1, 
      bBtn = 2,
      xBtn = 3,
      yBtn = 4, 
      leftBtn = 5,
      rightBtn = 6,
      backBtn = 7, 
      startBtn = 8, 
      leftStickBtn = 9,
      rightStickBtn = 10
};

enum POVPositions {
      UP = 0,
      UP_RIGHT = 45,
      RIGHT = 90,
      DOWN_RIGHT = 135,
      DOWN = 180,
      DOWN_LEFT = 225,
      LEFT = 270,
      UP_LEFT = 315,
};

class OI {
 public:
  OI();
  double GetJoystickX();
  double GetJoystickY();
  std::shared_ptr<frc::Joystick> joystick1;

  std::unique_ptr<frc::JoystickButton> btnArmToFloor;
  std::unique_ptr<ButtonPOV> btnArmToHab;
  std::unique_ptr<frc::JoystickButton> btnArmToHatch;
  std::unique_ptr<frc::JoystickButton> btnArmToSky;
  std::unique_ptr<frc::JoystickButton> btnArmToPreHab;

  std::unique_ptr<ButtonPOV> btnManualVacuum;
  std::unique_ptr<frc::JoystickButton> btnHabRoutine;

  std::unique_ptr<frc::JoystickButton> btnIntake;
  std::unique_ptr<frc::JoystickButton> btnOuttake;
  std::unique_ptr<ToggleButton> btnIntakeMode;
};
