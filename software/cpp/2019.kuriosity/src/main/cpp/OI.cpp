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
#include "commands/CmdHatchLowRocket.h"
#include "commands/CmdIntakePanel.h"
#include "commands/CmdGimbleRotateLeft.h"
#include "commands/CmdGimbleRotateRight.h"
#include "commands/CmdOverrideTurret.h"
#include "commands/CmdElevatorUpTest.h"
#include "commands/CmdElevatorDownTest.h"
#include "commands/CmdDriveBaseSlow.h"
#include "commands/CmdSeekPath.h"

OI::OI() {
  cout << "Run Robot OI" << endl;

  controller.reset(new frc::Joystick(0));

  //Drive Base
  btnDriveBaseSlow.reset(new frc::JoystickButton(controller.get(), leftStickBtn));
  btnDriveBaseSlow->WhileHeld(new CmdDriveBaseSlow());

  //Intake Outake
  btnCargoPodOut.reset(new frc::JoystickButton(controller.get(), leftBtn));
  btnCargoPodOut->WhileHeld(new CmdIntakeOutakeOut());

  btnCargoPodIn.reset(new frc::JoystickButton(controller.get(), rightBtn));
  btnCargoPodIn->WhileHeld(new CmdIntakeOutakeIn());

  //btnFollowLine.reset(new frc::JoystickButton(controller.get(), xBtn));
  //btnFollowLine->WhenPressed(new CmdHatchLowRocket());

  //Panel Affector
  btnDeployPanel.reset(new frc::JoystickButton(controller.get(), xBtn));
  btnDeployPanel->WhileHeld(new CmdOutputPanel(false));

  btnDeployFingers.reset(new frc::JoystickButton(controller.get(), bBtn));
  btnDeployFingers->WhileHeld(new CmdIntakePanel());

  //Gimble
  btnGimbleRotateLeft.reset(new frc::JoystickButton(controller.get(), backBtn));
  btnGimbleRotateLeft->WhileHeld(new CmdGimbleRotateLeft());

  btnGimbleRotateRight.reset(new frc::JoystickButton(controller.get(), startBtn));
  btnGimbleRotateRight->WhileHeld(new CmdGimbleRotateRight());

  btnOverride.reset(new frc::JoystickButton(controller.get(), rightStickBtn));
  btnOverride->WhileHeld(new CmdOverrideTurret());

  //Elevator
  btnUpTest.reset(new frc::JoystickButton(controller.get(), yBtn));
  btnUpTest->WhileHeld(new CmdElevatorUpTest());
  btnDownTest.reset(new frc::JoystickButton(controller.get(), aBtn));
  btnDownTest->WhileHeld(new CmdElevatorDownTest());
}
std::shared_ptr<frc::Joystick> OI::getJoystick0() {
   return joystick0;
}