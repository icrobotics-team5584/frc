// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc2/command/button/JoystickButton.h>

#include "RobotContainer.h"

#include "commands/cmdDriveNeoNT.h"

#include <frc/smartdashboard/SmartDashboard.h>

RobotContainer::RobotContainer() : 
CmdDrive{&SubDriveBase, &driverController},
SendableSparkMax{TestConstants::testMotorPort2, rev::CANSparkMaxLowLevel::MotorType::kBrushless}
{
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();

  frc::SmartDashboard::PutData("sendablesparkmax", &SendableSparkMax);

  SubDriveBase.SetDefaultCommand(CmdDrive);
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
  
  frc2::JoystickButton btnA{&driverController, Buttons::aBtn};

  btnA.WhileHeld(cmdDriveNeoNT(&SubMaxsNeo));
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
}
