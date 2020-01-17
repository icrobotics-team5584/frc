/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"
#include "Commands/CmdAutoRoutineOne.h"


OI::OI() {
  // Process operator interface input here.
  joystick1.reset(new frc::Joystick(0));
  btnAuto.reset(new frc::JoystickButton(joystick1.get(), 1));
  btnAuto->WhenPressed(new CmdAutoRoutineOne());

}

double OI::getJoystickX(){
  return joystick1->GetX();
}

double OI::getJoystickY(){
  return joystick1->GetY();
}