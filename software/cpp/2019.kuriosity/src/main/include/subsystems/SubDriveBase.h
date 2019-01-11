/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/WPILib.h>
#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <WPILib.h>

using namespace std;
using namespace frc;

class SubDriveBase : public frc::Subsystem {
 private:
  // Actuators
  shared_ptr<WPI_TalonSRX> _srxFrontLeft;
  shared_ptr<WPI_TalonSRX> _srxFrontRight;
  shared_ptr<WPI_TalonSRX> _srxBackLeft;
  shared_ptr<WPI_TalonSRX> _srxBackRight;
  unique_ptr<frc::DifferentialDrive> difDrive;
  
  // Sensors
  shared_ptr<AnalogInput> clsMid;
  shared_ptr<AnalogInput> clsFront;
  shared_ptr<Ultrasonic> ulsLeft;
  shared_ptr<Ultrasonic> ulsRight;

 public:
  SubDriveBase();
  void drive(double speed, double rotation);
  void InitDefaultCommand() override;
};
