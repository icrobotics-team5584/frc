/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"
#include "commands/CmdOutputPanel.h"
#include "commands/CmdIntakeOutakeOut.h"
#include "commands/CmdIntakeOutakeIn.h"
#include "commands/CmdIntakePanel.h"

OI::OI() {
  cout << "Run Robot OI" << endl;

  controller.reset(new frc::Joystick(0));

  btnCargoPodOut.reset(new frc::JoystickButton(controller.get(), leftBtn));
  btnCargoPodIn.reset(new frc::JoystickButton(controller.get(), rightBtn));
  btnDeployPanel.reset(new frc::JoystickButton(controller.get(), aBtn));
  btnIntakePanel.reset(new frc::JoystickButton(controller.get(), yBtn));

  btnIntakePanel->WhileHeld(new CmdIntakePanel());
  btnDeployPanel->WhileHeld(new CmdOutputPanel(false));
  btnCargoPodOut->WhileHeld(new CmdIntakeOutakeOut());
  btnCargoPodIn->WhileHeld(new CmdIntakeOutakeIn());
}