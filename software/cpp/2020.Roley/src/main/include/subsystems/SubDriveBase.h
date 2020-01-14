/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/drive/DifferentialDrive.h>
#include <ctre/Phoenix.h>
#include <frc/commands/Subsystem.h>
#include <frc/smartdashboard/SmartDashboard.h>

using namespace std;

class SubDriveBase : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

  
 public:
    
  shared_ptr<WPI_TalonSRX> _srxFrontLeft;
  shared_ptr<WPI_TalonSRX> _srxFrontRight;
  shared_ptr<WPI_TalonSRX> _srxBackLeft;
  shared_ptr<WPI_TalonSRX> _srxBackRight;

  unique_ptr<frc::DifferentialDrive> DiffDrive;
  
  SubDriveBase();
  void InitDefaultCommand() override;
  void drive(double speed, double rotation);
};
