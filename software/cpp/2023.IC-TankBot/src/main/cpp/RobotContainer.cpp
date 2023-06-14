
// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include "commands/CmdDriveRobot.h"
#include <frc2/command/button/Trigger.h>
#include <frc2/command/button/POVButton.h>
#include "subsystems/SubDriveBase.h"
#include "commands/GamePieceCommands.h"
#include "utilities/POVHelper.h"

RobotContainer::RobotContainer() {
  SubDriveBase::GetInstance().SetDefaultCommand(CmdDriveRobot(&_driverController));
  ConfigureBindings();
}

void RobotContainer::ConfigureBindings() {  
_driverController.A().WhileTrue(cmd::ShootBall());
_driverController.B().WhileTrue(cmd::StartShooting());
_driverController.X().WhileTrue(cmd::StopShooting());
POVHelper::Up(&_driverController).WhileTrue(cmd::StartFlyWheel());
POVHelper::Left(&_driverController).WhileTrue(cmd::StartIndexer());
POVHelper::Right(&_driverController).WhileTrue(cmd::StopIndexer());
POVHelper::Down(&_driverController).WhileTrue(cmd::StopFlyWheel());
}

/*frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return autos::ExampleAuto(&m_subsystem);
}*/
