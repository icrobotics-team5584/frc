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
#include <commands/CmdVacuum.h>
OI::OI():joystick1(0) {
  std::cout << "OI Started" << std::endl;
  // Process operator interface input here
  //btnAutoDrive.reset(new frc::JoystickButton(&joystick1, 2));
  btnArmPid.reset(new frc::JoystickButton(joystick1.get(), 1));
  std::cout << "button Init Finished" << std::endl;
  //btnArmPid->WhileHeld(new CmdMoveArm());
  btnClimber.reset(new frc::JoystickButton(joystick1.get(), 2));
  std::cout << "OI AFter btnClimber reset" << std::endl;
  btnClimber->WhileHeld(new CmdVacuum);
  std::cout << "OI Finished" << std::endl;
}



double OI::GetJoystickX(){
  //joystick1.GetX();


}

double OI::GetJoystickY(){
  //joystick1.GetY();


}

