/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"
#include <frc/WPILib.h>
#include "commands/CmdAngleTurn.h"
#include "commands/CmdAutoDrive.h"
#include "commands/CmdMoveArm.h"
#include "commands/CmdIntake.h"
#include "commands/CmdOuttake.h"
#include "commands/CmdVacuum.h"
#include "commands/CmdArmToFloor.h"
#include "commands/CmdArmToHab.h"
#include "commands/CmdArmToHatch.h"
#include "commands/CmdArmToPreHab.h"
#include "commands/CmdArmToSky.h"
#include <commands/CmdArmForward.h>
#include <commands/CmdArmBackwards.h>

OI::OI() {
  std::cout << "OI Started" << std::endl;
  joystick1.reset(new Joystick(0));
  
  // Create Buttons
  btnArmToFloor.reset(new frc::JoystickButton(joystick1.get(), aBtn));
  btnArmToHab.reset(new frc::JoystickButton(joystick1.get(), startBtn));
  btnArmToHatch.reset(new frc::JoystickButton(joystick1.get(), bBtn));
  btnArmToSky.reset(new frc::JoystickButton(joystick1.get(), xBtn));
  btnArmToPreHab.reset(new frc::JoystickButton(joystick1.get(), backBtn)); //Listed as 'select' in drive team doc
  
  btnManualVacuum.reset(new ButtonPOV(joystick1.get(), UP));

  btnIntake.reset(new frc::JoystickButton(joystick1.get(), leftBtn));   // Does not yet match drive team doc
  btnOuttake.reset(new frc::JoystickButton(joystick1.get(), rightBtn)); // Does not yet match drive team doc
  btnIntakeMode.reset(new frc::JoystickButton(joystick1.get(), yBtn));  // Does not yet match drive team doc
  
  std::cout << "button Init Finished" << std::endl;

  // Map Buttons to Commands 
  btnArmToFloor->WhileHeld(new CmdArmToFloor());
  btnArmToHab->WhileHeld(new CmdArmToHab());
  btnArmToHatch->WhileHeld(new CmdArmToHatch());
  btnArmToSky->WhileHeld(new CmdArmToSky());
  btnArmToPreHab->WhileHeld(new CmdArmToPreHab());

  btnManualVacuum->WhileHeld(new CmdVacuum());

  btnIntake->WhileHeld(new CmdIntake());
  btnOuttake->WhileHeld(new CmdOuttake());
  //btnIntakeMode->todo: Toggle between two commands
  
  std::cout << "OI Finished" << std::endl;
}

double OI::GetJoystickX() {
  return joystick1->GetX();
}

double OI::GetJoystickY() {
  return joystick1->GetY();
}

