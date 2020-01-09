/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include "commands/CmdIntake.h"
#include "commands/CmdOuttake.h"

OI::OI() {
  std::cout<< "OI Started" << std::endl;

  joystick1.reset(new frc::Joystick(0));

  std::cout<< "1" << std::endl;

  btnIntake.reset(new frc::JoystickButton(joystick1.get(), leftBtn));

  std::cout<< "2" << std::endl;

  btnOuttake.reset(new frc::JoystickButton(joystick1.get(), rightBtn));

  std::cout<< "3" << std::endl;


  btnIntake->WhileHeld(new CmdIntake());

  std::cout<< "4" << std::endl;

  btnOuttake->WhileHeld(new CmdOuttake());

  std::cout<< "OI Ended" << std::endl;
}
