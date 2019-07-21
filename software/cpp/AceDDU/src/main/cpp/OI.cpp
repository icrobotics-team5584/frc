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
#include "commands/CmdVacuumReverse.h"
#include "commands/CmdArmToFloor.h"
#include "commands/CmdArmToHab.h"
#include "commands/CmdArmToHatch.h"
#include "commands/CmdArmToPreHab.h"
#include "commands/CmdArmToSky.h"
#include "commands/CmdArmToRocket.h"
#include <commands/CmdArmForward.h>
#include <commands/CmdArmBackwards.h>
#include "commands/CmdCloseIntake.h"
#include "commands/CmdOpenIntake.h"
#include "subsystems/SubIntake.h"
#include "commands/CmdHabRoutine.h"
#include "commands/CmdSlowDown.h"

OI::OI() {
  std::cout << "OI Started" << std::endl;
  joystick1.reset(new Joystick(0));
  
  // Create Buttons
  btnArmToFloor.reset(new frc::JoystickButton(joystick1.get(), aBtn));
  btnArmToHatch.reset(new frc::JoystickButton(joystick1.get(), bBtn));
  btnArmToSky.reset(new frc::JoystickButton(joystick1.get(), xBtn));
  btnArmToPreHab.reset(new frc::JoystickButton(joystick1.get(), backBtn)); //Listed as 'select' in drive team doc
  btnArmToRocket.reset(new AxisButton(joystick1.get(), triggerL));
  btnSlowDown.reset(new AxisButton(joystick1.get(), triggerR));
  
  btnManualVacuum.reset(new ButtonPOV(joystick1.get(), UP));
  btnManualVacuumReverse.reset(new ButtonPOV(joystick1.get(), LEFT));
  btnArmToHab.reset(new ButtonPOV(joystick1.get(), DOWN));
  btnHabRoutine.reset(new frc::JoystickButton(joystick1.get(), startBtn));

  btnIntake.reset(new frc::JoystickButton(joystick1.get(), leftBtn));   // Does not yet match drive team doc
  btnOuttake.reset(new frc::JoystickButton(joystick1.get(), rightBtn)); // Does not yet match drive team doc
  btnIntakeMode.reset(new ToggleButton(joystick1.get(), yBtn));  // Does not yet match drive team doc
  
  std::cout << "button Init Finished" << std::endl;

  // Map Buttons to Commands 
  btnArmToFloor->WhileHeld(new CmdArmToFloor());
  btnArmToHab->WhileHeld(new CmdArmToHab());
  btnArmToHatch->WhileHeld(new CmdArmToHatch());
  btnArmToSky->WhileHeld(new CmdArmToSky());
  btnArmToPreHab->WhileHeld(new CmdArmToPreHab());
  btnArmToRocket->WhileHeld(new CmdArmToRocket());
  btnSlowDown->WhileHeld(new CmdSlowDown());

  btnManualVacuum->WhileHeld(new CmdVacuum());
  
  btnManualVacuumReverse->WhileHeld(new CmdVacuumReverse());

  btnHabRoutine->WhileHeld(new CmdHabRoutine());

  btnIntake->WhileHeld(new CmdIntake());
  btnOuttake->WhileHeld(new CmdOuttake());

  btnIntakeMode->SetCommand(new CmdOpenIntake(), new CmdCloseIntake());
  
  

  //btnIntakeMode->todo: Toggle between two commands
  
  std::cout << "OI Finished" << std::endl;
}

double OI::GetJoystickX() {
  return joystick1->GetX();
}

double OI::GetJoystickY() {
  return joystick1->GetY();
}

double OI::GetLeftAsix(){
  return btnSlowDown->GetAxis();
}

double OI::GetRightAsix(){
  return btnArmToRocket->GetAxis();
}
