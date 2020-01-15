/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include<iostream>
#include<ctre/phoenix.h>
#include<frc/drive/DifferentialDrive.h>
#include<frc/smartdashboard/SmartDashboard.h>





class SubDriveBase : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  std::shared_ptr<WPI_TalonSRX>_srxFrontLeft;
  std::shared_ptr<WPI_TalonSRX>_srxFrontRight;
  std::shared_ptr<WPI_TalonSRX>_srxBackLeft;
  std::shared_ptr<WPI_TalonSRX>_srxBackRight;
  
  std::unique_ptr<frc::DifferentialDrive>DiffDrive;

 public:
  SubDriveBase();
  void InitDefaultCommand() override;
  void Drive(double speed, double rotation);
};


/*

Things needed:

create shared pointers to Talon motor controllers in SubDriveBase.h
initialise those pointers to objects (.reset(...)) in SubDriveBase.cpp
Create pointer to differential drive in subdrivebase.h
initialise that pointer to an object in subdrivebase.cpp
make a drive(speed, direction) function in subdrivebase class


Create static shared pointer to subdrivebase in Robot.h
Forward declare shared ponter to subdrivevase in Robot.cpp

make functions in OI to get joystick values

make a drive command
run the drivebase's drive function from the drive command using the oi functions to get joystick valuse
set drive command as default command of drive base subsystem




*/