/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "frc/Joystick.h"
#include "frc/buttons/JoystickButton.h"

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

enum Triggers {
      triggerL = 2,
      triggerR = 3,
};

class OI {
 public:
  OI();
  double getJoystickX();
  double getJoystickY();
 private:
  std::unique_ptr<frc::Joystick> joystick1;
  std::unique_ptr<frc::JoystickButton> btnIntake;
  std::unique_ptr<frc::JoystickButton> btnOuttake;
};
