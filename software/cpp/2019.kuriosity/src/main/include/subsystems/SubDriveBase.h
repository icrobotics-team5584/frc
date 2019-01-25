/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/WPILib.h>
#include <frc/commands/Subsystem.h>
#include <pathfinder.h>

#include <ctre/Phoenix.h>
#include <AHRS.h>

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
  shared_ptr<DigitalInput> _clsMid;
  shared_ptr<DigitalInput> _clsFront;
  shared_ptr<Ultrasonic> _ulsGimble;
  shared_ptr<Ultrasonic> _ulsBottom;
  shared_ptr<AHRS> _ahrsNavXGyro;
  shared_ptr<DigitalInput> _clsLineLeft;
  shared_ptr<DigitalInput> _clsLineRight;

  // Robot constants
  const double WHEEL_DIAMETER = 0.1016; // in meters (0.2032 for dizzy)
  const int ENCODER_TICS_PER_ROTATION = 4096; // (214 for dizzy)
  double metersPerRotation; // calculated in constructor

  int pathLength; //path length

  void setTalControlMode(ControlMode controlMode);
  const double VELOCITY_CONVERSION_FACTOR = 1280.4; //for when converting m/s to p/100ms
 
 public:
  SubDriveBase();
  void InitDefaultCommand() override;

  // Drive functions
  void tankDriveVelocity(double leftVelocity, double rightVelocity);
  void drive(double speed, double rotation);
  void tankDrive(double leftSpeed, double rightSpeed);
  void brakeRobot();
  Segment* generatePath();
  int getPathLength();

  // Encoder functions
  void zeroEncoders();
  double getRawLeftEncoder();
  double getRawRightEncoder();
  double getDistanceTravelled();
  double getVelocity();

  // Gyro functions
  void resetYaw();
  double getYaw();

  // Colour Sensor functions
  bool frontHasReachedLine();
  bool midHasReachedLine();
  bool isLeftClsOnLine();
  bool isRightClsOnLine();

  // Ultrasonic functions
  double getDistanceToObstical();
  bool isBayEmpty();
};
