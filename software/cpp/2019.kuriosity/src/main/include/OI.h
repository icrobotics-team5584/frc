#pragma once

#include <iostream>
#include <frc/WPILib.h>
#include "ButtonPOV.h"
#include "AxisButton.h"
#include "LimitButton.h"

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

enum Axis {
  leftAxisTrigger = 2,
  rightAxisTrigger = 3,
};

enum ElevatorHeight {
  bottom = 0,
};

class OI {
 public:
  shared_ptr<frc::Joystick> controller;
  shared_ptr<frc::JoystickButton> btnCargoPodOut;
  shared_ptr<frc::JoystickButton> btnCargoPodIn;
  OI();
  std::shared_ptr<frc::Joystick> getJoystick0();
private:
  unique_ptr<frc::JoystickButton> btnFollowLine;
  unique_ptr<frc::JoystickButton> btnMotionProfile;
  unique_ptr<frc::JoystickButton> btnEncoderDrive;
  unique_ptr<AxisButton> btnStopAtLine;

  unique_ptr<frc::JoystickButton> btnDeployPanel;
  unique_ptr<frc::JoystickButton> btnDeployFingers; 
  unique_ptr<frc::JoystickButton> btnSeekPath;
  unique_ptr<frc::JoystickButton> btnGimbleRotateLeft;
  unique_ptr<frc::JoystickButton> btnGimbleRotateRight; //Moved to overide stick (right stick with press)
  unique_ptr<ButtonPOV> povBtnGimblePidLeft;
  unique_ptr<ButtonPOV> povBtnGimblePidCentre;
  unique_ptr<ButtonPOV> povBtnGimblePidRight;
  unique_ptr<frc::JoystickButton> btnSeekRocketSide;
  unique_ptr<AxisButton> btnDriveBaseSlow;
  unique_ptr<frc::JoystickButton> btnElevatorToPos;
  unique_ptr<frc::JoystickButton> btnElevatorToBottom;

  unique_ptr<frc::JoystickButton> btnOverride;

  unique_ptr<LimitButton> lmtPIDTop;
  unique_ptr<LimitButton> lmtPIDBottom;

  std::shared_ptr<frc::Joystick> joystick0;

  unique_ptr<frc::JoystickButton> btnUpTest;
  unique_ptr<frc::JoystickButton> btnDownTest;
};
