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
#include "commands/CmdGimblePidLeft.h"
#include "commands/CmdGimblePidCentre.h"
#include "commands/CmdGimblePidRight.h"
#include "commands/CmdOverrideTurret.h"
#include "commands/CmdElevatorUpTest.h"
#include "commands/CmdElevatorDownTest.h"
#include "commands/CmdDriveBaseSlow.h"
#include "commands/CmdElevatorToPosition.h"
#include "commands/CmdElevatorLimit.h"
#include "commands/CmdElevatorPIDBottomStop.h"
#include "commands/CmdElevatorPIDTopStop.h"
#include "commands/CmdSeekPath.h"
#include "commands/CmdMotionProfile.h"
#include "commands/CmdEncoderDrive.h"
#include "commands/CmdStopAtLine.h"
#include "commands/CmdSeekRocketSide.h"
#include "commands/CmdCargoIntakeOut.h"
#include "commands/CmdCargoIntakeIn.h"
#include "commands/CmdClimberDeploy.h"
#include "commands/CmdGimblePIDLeftStop.h"
#include "commands/CmdGimblePIDRightStop.h"

#include "commands/CmdGimbleOverrideLeft.h"
#include "commands/CmdGimbleOverrideRight.h"
OI::OI() {
  cout << "Run Robot OI" << endl;

  controller.reset(new frc::Joystick(0));
  controllerReverse.reset(new frc::Joystick(1));

  //Drive Base
  btnDriveBaseSlow.reset(new AxisButton(controller.get(), leftAxisTrigger));
  btnDriveBaseSlow->WhileHeld(new CmdDriveBaseSlow(false));

  btnDriveBaseSlowControllerReverse.reset(new AxisButton(controllerReverse.get(), leftAxisTrigger));
  btnDriveBaseSlowControllerReverse->WhileHeld(new CmdDriveBaseSlow(true));

  btnSeekRocketSide.reset(new AxisButton(controller.get(), rightAxisTrigger));
  btnSeekRocketSide->WhileHeld(new CmdSeekRocketSide());

  btnIntakeOut.reset(new frc::JoystickButton(controller.get(), rightBtn));
  btnIntakeOut->WhenPressed(new CmdCargoIntakeOut());

  btnIntakeOut->WhenReleased(new CmdCargoIntakeIn());

  //Intake Outake
  btnCargoPodOut.reset(new frc::JoystickButton(controller.get(), leftBtn));
  btnCargoPodOut->WhileHeld(new CmdIntakeOutakeOut());

  // btnSeekRocketSide.reset(new frc::JoystickButton(controller.get(), yBtn));
  // btnSeekRocketSide->WhenPressed(new CmdSeekRocketSide());
  //btnFollowLine.reset(new frc::JoystickButton(controller.get(), xBtn));
  //btnFollowLine->WhenPressed(new CmdHatchLowRocket());

  //Panel Affector
  btnDeployPanel.reset(new frc::JoystickButton(controller.get(), xBtn));
  btnDeployPanel->WhileHeld(new CmdOutputPanel(false));

  btnDeployFingers.reset(new frc::JoystickButton(controller.get(), bBtn));
  btnDeployFingers->WhileHeld(new CmdIntakePanel());

  //Gimble
  //btnGimbleRotateLeft.reset(new frc::JoystickButton(controller.get(), backBtn));
  //btnGimbleRotateLeft->WhileHeld(new CmdGimbleRotateLeft());
  //btnGimbleRotateRight.reset(new frc::JoystickButton(controller.get(), startBtn));
  //btnGimbleRotateRight->WhileHeld(new CmdGimbleRotateRight());

  //Gimble PID Controls 
  povBtnGimblePidLeft.reset(new ButtonPOV(controller.get(), 270));
  povBtnGimblePidLeft->WhenPressed(new CmdGimblePidLeft());
 
  povBtnGimblePidRight.reset(new ButtonPOV(controller.get(), 90));
  povBtnGimblePidRight->WhenPressed(new CmdGimblePidRight());
  povBtnGimblePidCentre.reset(new ButtonPOV(controller.get(), 0));
  povBtnGimblePidCentre->WhenPressed(new CmdGimblePidCentre());
  
  btnOverride.reset(new frc::JoystickButton(controller.get(), rightStickBtn));
  btnOverride->WhileHeld(new CmdOverrideTurret());

  lmtPIDTop.reset(new LimitButton(Robot::_robotMap->subElevatorLimitTop, false));
  lmtPIDTop->WhenPressed(new CmdElevatorPIDTopStop());
  lmtPIDBottom.reset(new LimitButton(Robot::_robotMap->subElevatorLimitBottom, true));
  lmtPIDBottom->WhenPressed(new CmdElevatorPIDBottomStop());

  lmtPIDLeft.reset(new LimitButton(Robot::_robotMap->subGimbleLimitLeft, false));
  lmtPIDLeft->WhenPressed(new CmdGimblePIDLeftStop());
  lmtPIDRight.reset(new LimitButton(Robot::_robotMap->subGimbleLimitRight, false));
  lmtPIDRight->WhenPressed(new CmdGimblePIDRightStop());

  btnClimber.reset(new frc::JoystickButton(controller.get(), backBtn));
  btnClimber->WhileHeld(new CmdClimberDeploy());

  //Elevator
  //btnUpTest.reset(new frc::JoystickButton(controller.get(), yBtn));
  //btnUpTest->WhileHeld(new CmdElevatorUpTest());
  //btnDownTest.reset(new frc::JoystickButton(controller.get(), aBtn));
  //btnDownTest->WhileHeld(new CmdElevatorDownTest());
  btnElevatorToPos.reset(new frc::JoystickButton(controller.get(), yBtn));
  btnElevatorToPos->WhenPressed(new CmdElevatorToPosition(false, false, 0));

  btnElevatorToBottom.reset(new frc::JoystickButton(controller.get(), aBtn));
  btnElevatorToBottom->WhenPressed(new CmdElevatorToPosition(true, false, 0));
}

std::shared_ptr<frc::Joystick> OI::getJoystick(int id) {
  if( id == 1 ) {
    return controllerReverse;
  } else {
    return controller;
  }
}