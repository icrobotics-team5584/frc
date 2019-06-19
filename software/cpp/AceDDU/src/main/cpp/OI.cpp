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
#include "commands/CmdIntake.h"
#include "commands/CmdOuttake.h"
#include <frc/WPILib.h>

OI::OI():joystick1(0) {
  std::cout << "OI Started" << std::endl;
  // Process operator interface input here
  //btnAutoDrive.reset(new frc::JoystickButton(&joystick1, 2));
  btnArmPid.reset(new frc::JoystickButton(joystick1.get(), 1));
  btnIntake.reset(new frc::JoystickButton(joystick1.get(), leftBtn));
  btnIntake->WhileHeld(new CmdIntake());
  btnOuttake.reset(new frc::JoystickButton(joystick1.get(), rightBtn));
  btnIntake->WhileHeld(new CmdOuttake());
  btnIntakeMode.reset(new frc::JoystickButton(joystick1.get(), xBtn));
  //TODO:firgure out how to use toggle
  //btnIntake->ToggleWhenPressed(new CmdOpenIntake(),new CmdCloseIntake);
  
  std::cout << "buttonInit Finished" << std::endl;
  //btnArmPid->WhileHeld(new CmdMoveArm());
  std::cout << "OI Finished" << std::endl;
}



double OI::GetJoystickX(){
  //joystick1.GetX();


}

double OI::GetJoystickY(){
  //joystick1.GetY();


}

