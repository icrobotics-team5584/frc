/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <iostream>
#include <frc/WPILib.h>

using namespace std;

enum Buttons {
     aBtn= 1,
     bBtn= 2,
     xBtn = 3,
     yBtn = 4,
     leftBtn = 5,
     rightBtn = 6,
     backBtn = 7,
     startBtn = 8,
     leftStickBtn = 9,
     rightStickBtn =10
};


class OI {
 public:
  shared_ptr<frc::Joystick> controller;
  shared_ptr<frc::JoystickButton> btnCargoPodOut;
  shared_ptr<frc::JoystickButton> btnCargoPodIn;
  OI();

private:
  unique_ptr<frc::JoystickButton> btnFollowLine;
  unique_ptr<frc::JoystickButton> btnDeployPanel;
  unique_ptr<frc::JoystickButton> btnDeployFingers; 
  unique_ptr<frc::JoystickButton> btnVisionDrive; 
};
