/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "frc/drive/DifferentialDrive.h"
#include<iostream>
#include "RobotMap.h"
#include <ctre/Phoenix.h>
#include "frc/commands/Subsystem.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <AHRS.h>
#include "Utilities/PosEncoderGyro.h"
using namespace std;
class SubDriveBase : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  
  shared_ptr<WPI_TalonSRX> _srxFrontLeft;
  shared_ptr<WPI_TalonSRX> _srxFrontRight;
  shared_ptr<WPI_TalonSRX> _srxBackLeft;
  shared_ptr<WPI_TalonSRX> _srxBackRight;

  unique_ptr<frc::DifferentialDrive> DiffDrive;

  shared_ptr<AHRS> ahrsNavXGyro;

  shared_ptr<WPI_TalonSRX> _srxAutoXAxis;

// Robot constants
  const double WHEEL_DIAMETER = 0.0508; // in meters (0.1016 for lofty)(0.1524 for dizzy) (0.0508 for dolly)
  const int ENCODER_TICS_PER_ROTATION = 4096; // 
  const double pi = 3.1415926535897932384626433832795028841971693993751;
  double metersPerRotation; // calculated in constructor
  
// PID Values
  double Kp = -0.5;
  double Ki = 0.0;
  double Kd = -50.0;
  double previousError;
  double intergral = 0;
  double AutoSpeed = 0.8;
 public:
  SubDriveBase();
  void InitDefaultCommand() override;
  void drive(double speed, double rotation, bool squaredInputs = true);
  double getYaw();
  double getDistanceTravelled();
  void zeroEncoders();
  void autoEncoderDrive(double target);
  void resetYaw();
  void Periodic() override;
  bool isNavxCal();
};
