/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include <frc/WPILib.h>

OI::OI() {
  // Process operator interface input here.
  joystick1.reset(new frc::Joystick(0));

}

double OI::getJoystickX(){
  return joystick1->GetX();
}

double OI::getJoystickY(){
  return joystick1->GetY();
}