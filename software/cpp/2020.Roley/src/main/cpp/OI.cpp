/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"
#include "commands/CmdShooterShoot.h"
#include "commands/CmdRollStorage.h"
#include "commands/CmdRollStorageBack.h"

#include "commands/CmdIntake.h"
#include "commands/CmdOuttake.h"
#include <frc/Joystick.h>

#include "commands/CmdDriveSlowDown.h"
OI::OI() {
  std::cout<< "OI Started" << std::endl;

  joystick1.reset(new frc::Joystick(0));
  btnShoot.reset(new frc::JoystickButton(joystick1.get(),aBtn));
  btnForward.reset(new frc::JoystickButton(joystick1.get(),xBtn));
  btnBackward.reset(new frc::JoystickButton(joystick1.get(),yBtn));

  btnShoot->WhileHeld(new CmdShooterShoot);
  btnForward->WhileHeld(new CmdRollStorage);
  btnBackward->WhileHeld(new CmdRollStorageBack);
  btnSlowDown.reset(new AxisButton(joystick1.get(), triggerL));

  btnSlowDown->WhileHeld(new CmdDriveSlowDown());

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



double OI::getJoystickX(){
  return joystick1->GetX();
}

double OI::getJoystickY(){
  return joystick1->GetY();
}



double OI::GetRightAsix(){
  return btnSlowDown->GetAxis();
}