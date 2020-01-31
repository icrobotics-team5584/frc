/*----------------------------------------------------------------------------*/
/* OI.h                                                                       */
/*----------------------------------------------------------------------------*/

#pragma once

#include <iostream>

#include "frc/buttons/JoystickButton.h"
#include "subsystems/AxisButton.h"
#include "frc/Joystick.h"

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
  double getJoystickRawAxis(Triggers trigger);
  double GetRightAsix();
  
 private:
  //Joystick pointers
  std::unique_ptr<frc::Joystick> joystick1;
  std::unique_ptr<frc::JoystickButton> btnAuto;

  //Button pointers
  std::unique_ptr<AxisButton> btnSlowDown;
  std::unique_ptr<frc::JoystickButton> btnShoot;
  std::unique_ptr<frc::JoystickButton> btnForward;
  std::unique_ptr<frc::JoystickButton> btnBackward;
  std::unique_ptr<frc::JoystickButton> btnIntake;
  std::unique_ptr<frc::JoystickButton> btnOuttake;
  std::unique_ptr<frc::JoystickButton> btnClimb;
};
