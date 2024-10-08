/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <AHRS.h>

using namespace std;
class SubDriveBase : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  shared_ptr<WPI_TalonSRX> _srxFrontLeft;
  shared_ptr<WPI_TalonSRX> _srxFrontRight;
  shared_ptr<WPI_TalonSRX> _srxBackLeft;
  shared_ptr<WPI_TalonSRX> _srxBackRight;
  unique_ptr<DifferentialDrive> difDrive;

  //sensors
  shared_ptr<Ultrasonic> _ulsLeft;
  // shared_ptr<DigitalInput> _ulsEchoLeft;
  shared_ptr<AHRS> _ahrsNavXGyro;
  shared_ptr<DigitalInput> _clsLeft;
  shared_ptr<AnalogInput> _clsFront;

 public:
  SubDriveBase();
  void drive(double speed, double rotation);
  void InitDefaultCommand() override;
  void getRange();
  bool hasReachedLine();
  double getYaw();
  void resetYaw();
 // bool isBayEmpty();
  void brakeRobot();
  void getClsData();
};
