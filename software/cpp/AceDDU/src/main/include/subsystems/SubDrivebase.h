/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <frc/WPILib.h>


class SubDrivebase : public frc::Subsystem, public frc::PIDOutput{

 private:
  const double WHEEL_DIAMETER{0.1016};
  double circumference;
  const double PI {3.14159265359};
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

 public:
  SubDrivebase();
  std::shared_ptr<WPI_TalonSRX> srxFrontLeft;
  std::shared_ptr<WPI_TalonSRX> srxFrontRight;
  std::shared_ptr<WPI_TalonSRX> srxBackRight;
  std::shared_ptr<WPI_TalonSRX> srxBackLeft;
  std::shared_ptr<frc::DifferentialDrive> diffdrive;
  std::shared_ptr<PigeonIMU> imu;
  void InitDefaultCommand() override;
  void drive(double speed, double rotation);
  int get_angle();
  void PIDWrite(double output);
  double get_distance(); 
  int get_RightEncoder();
  int get_LeftEncoder();
  void resetEncoders();

  /*
  Left = talon 3
  Right = talon 4
  */


};

