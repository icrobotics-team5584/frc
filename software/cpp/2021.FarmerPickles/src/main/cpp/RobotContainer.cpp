// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc2/command/button/JoystickButton.h>

#include "RobotContainer.h"


#include <frc/smartdashboard/SmartDashboard.h>

RobotContainer::RobotContainer() : 
CmdDrive{&SubDriveBase, &driverController},
//Set up our Nice Max's.
SPMTest1{TestConstants::testMotor1, rev::CANSparkMaxLowLevel::MotorType::kBrushless},
SPMTest2{TestConstants::testMotor2, rev::CANSparkMaxLowLevel::MotorType::kBrushless},
SPMTest3{TestConstants::testMotor3, rev::CANSparkMaxLowLevel::MotorType::kBrushless}
{
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();

  frc::SmartDashboard::PutData("Max", &SPMTest1);
  frc::SmartDashboard::PutData("MaxMax", &SPMTest2);
  frc::SmartDashboard::PutData("MaxMaxMax", &SPMTest3);

  SubDriveBase.SetDefaultCommand(CmdDrive);
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
  
  frc2::JoystickButton btnA{&driverController, Buttons::aBtn};

}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return NULL;
}
