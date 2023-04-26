// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include "commands/CmdDriveRobot.h"
#include <frc2/command/button/Trigger.h>
#include "subsystems/SubDriveBase.h"

RobotContainer::RobotContainer() {
  SubDriveBase::GetInstance().SetDefaultCommand(CmdDriveRobot(&_driverController));
  ConfigureBindings();
}

void RobotContainer::ConfigureBindings() {  

}

/*frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return autos::ExampleAuto(&m_subsystem);
}*/
