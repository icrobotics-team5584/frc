/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"
#include "commands/CmdAngleTurn.h"
#include"commands/CmdAutoDrive.h"
#include "commands/CmdMoveArm.h"
#include <frc/WPILib.h>
#include "commands/CmdInspireArm.h"

OI::OI() {
  joystick1.reset(new Joystick(0));
  std::cout << "OI Started" << std::endl;
  // Process operator interface input here
  //btnAutoDrive.reset(new frc::JoystickButton(&joystick1, 2));
  btnArmPid.reset(new frc::JoystickButton(joystick1.get(), 1));
  std::cout << "buttonInit Finished" << std::endl;
  //btnArmPid->WhileHeld(new CmdMoveArm());
  btnInspireArm.reset(new frc::JoystickButton(joystick1.get(), 2));
  btnInspireArm->WhileHeld(new CmdInspireArm());
  std::cout << "OI Finished" << std::endl;
}



double OI::GetJoystickX(){
  //joystick1.GetX();


}

double OI::GetJoystickY(){
  //joystick1.GetY();


}

