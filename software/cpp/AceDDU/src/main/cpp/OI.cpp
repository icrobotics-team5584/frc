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

#include "commands/CmdArmToFloor.h"
#include "commands/CmdArmToHab.h"
#include "commands/CmdArmToHatch.h"
#include "commands/CmdArmToPreHab.h"
#include "commands/CmdArmToSky.h"

#include <commands/CmdArmForward.h>
#include <commands/CmdArmBackwards.h>

OI::OI() {
  joystick1.reset(new Joystick(0));
  std::cout << "OI Started" << std::endl;
  // Process operator interface input here
  //btnAutoDrive.reset(new frc::JoystickButton(&joystick1, 2));
  btnArmToFloor.reset(new frc::JoystickButton(joystick1.get(), 3));
  btnArmToHab.reset(new frc::JoystickButton(joystick1.get(), 4));
  btnArmToHatch.reset(new frc::JoystickButton(joystick1.get(), 5));
  btnArmToSky.reset(new frc::JoystickButton(joystick1.get(), 6));
  btnArmToPreHab.reset(new frc::JoystickButton(joystick1.get(), 2));
  std::cout << "button Init Finished" << std::endl;
  //btnArmPid->WhileHeld(new CmdMoveArm());
  btnClimber.reset(new frc::JoystickButton(joystick1.get(), 1));
  std::cout << "OI AFter btnClimber reset" << std::endl;
  btnClimber->WhileHeld(new CmdVacuum());
  //btnArm0->WhileHeld(new cmdArmPos0());


  btnArmForward.reset(new frc::JoystickButton(joystick1.get(), 3));
  btnArmBackwards.reset(new frc::JoystickButton(joystick1.get(), 4));

  btnArmForward->WhileHeld(new CmdArmForward());
  btnArmBackwards->WhileHeld(new CmdArmBackwards());

  btnArmToFloor->WhileHeld(new CmdArmToFloor());
  btnArmToHab->WhileHeld(new CmdArmToHab());
  btnArmToHatch->WhileHeld(new CmdArmToHatch());
  btnArmToSky->WhileHeld(new CmdArmToSky());
  btnArmToPreHab->WhileHeld(new CmdArmToPreHab());

  std::cout << "OI Finished" << std::endl;
}

double OI::GetJoystickX(){
  joystick1->GetX();


}

double OI::GetJoystickY(){
  joystick1->GetY();


}

