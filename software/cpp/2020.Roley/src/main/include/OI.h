/*----------------------------------------------------------------------------*/
/* OI.h                                                                       */
/*----------------------------------------------------------------------------*/

#pragma once

#include <iostream>

#include "frc/buttons/JoystickButton.h"
#include "subsystems/AxisButton.h"
#include "frc/Joystick.h"

#include "Utilities/ButtonPOV.h"

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
  double getJoystick2X();
  double getJoystick2Y();
  double getJoystickRawAxis(Triggers trigger);
  double GetRightAsix();
  bool GetOverride();
  
  
 private:
  //Joystick pointers
  std::unique_ptr<frc::Joystick> joystick1;
  std::unique_ptr<frc::JoystickButton> btnAuto;

  //Button pointers
  std::unique_ptr<AxisButton> btnSlowDown;
  std::unique_ptr<frc::JoystickButton> btnDeployIntake;
  std::unique_ptr<frc::JoystickButton> btnShoot;
  std::unique_ptr<frc::JoystickButton> btnForward;
  std::unique_ptr<frc::JoystickButton> btnBackward;
  std::unique_ptr<frc::JoystickButton> btnIntake;
  std::unique_ptr<frc::JoystickButton> btnOuttake;
  std::unique_ptr<frc::JoystickButton> btnClimb;
  std::unique_ptr<frc::JoystickButton> btnReleaseBuddyClimber;
  std::unique_ptr<frc::JoystickButton> btnOverride;
  std::unique_ptr<frc::JoystickButton> btnRatchets;
  std::unique_ptr<frc::JoystickButton> btnIntakeReverse;
  std::unique_ptr<frc::JoystickButton> btnShuffle;

  std::unique_ptr<frc::JoystickButton> btnReverseStorage;
  std::unique_ptr<ButtonPOV> btnElevaterUp;
  std::unique_ptr<ButtonPOV> btnElevaterDown;
  std::unique_ptr<ButtonPOV> btnElevaterBuddy;

  };
