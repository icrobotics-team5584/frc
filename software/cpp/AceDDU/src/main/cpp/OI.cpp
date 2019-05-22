/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"
#include "commands/CmdAngleTurn.h"
#include"commands/CmdAutoDrive.h"
#include <frc/WPILib.h>

OI::OI():joystick1(0) {
  // Process operator interface input here
  //btnAutoDrive.reset(new frc::JoystickButton(&joystick1, 2));
}



double OI::GetJoystickX(){
  joystick1.GetX();


}

double OI::GetJoystickY(){
  joystick1.GetY();


}

