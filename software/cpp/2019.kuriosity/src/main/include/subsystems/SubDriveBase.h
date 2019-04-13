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

#include "RightVelocitySource.h"
#include "LeftVelocitySource.h"

using namespace std;
using namespace frc;

enum ColourSensor {CLS_LEFT, CLS_RIGHT};
enum UltrasonicSensor {LEFT, RIGHT};

class SubDriveBase : public frc::Subsystem {
 private:
  // Actuators
  shared_ptr<WPI_TalonSRX> _srxFrontLeft;
  shared_ptr<WPI_TalonSRX> _srxFrontRight;
  shared_ptr<WPI_TalonSRX> _srxBackLeft;
  shared_ptr<WPI_TalonSRX> _srxBackRight;
  unique_ptr<frc::DifferentialDrive> difDrive;
  unique_ptr<PIDController> leftVelocityController;
  unique_ptr<PIDController> rightVelocityController;
  LeftVelocitySource* leftVelocitySource;
  RightVelocitySource* rightVelocitySource;

  // Sensors
  shared_ptr<DigitalInput> _clsLeft;
  shared_ptr<DigitalInput> _clsRight;
  // shared_ptr<DigitalInput> _clsMidLeft;
  // shared_ptr<DigitalInput> _clsMidRight;
  shared_ptr<Ultrasonic> _ulsLeft;
  shared_ptr<Ultrasonic> _ulsRight;
  shared_ptr<AHRS> _ahrsNavXGyro;
  

  // Robot constants
  const double WHEEL_DIAMETER = 0.1524; // in meters (0.1016 for lofty)(0.1524 for dizzy)
  const int ENCODER_TICS_PER_ROTATION = 4096; // 
  double metersPerRotation; // calculated in constructor

  int pathLength; //path length
  double scaleFactor = (WHEEL_DIAMETER * 3.1459265)/4096;
  Timer timer;
  
	double kTimeoutMs = 30;
  double kPIDLoopIdx = 0;
  double kSlotIdx = 0;
 
 public:
  const double WHEEL_BASE_WIDTH =  0.6;
  SubDriveBase();
  void InitDefaultCommand() override;

  // Drive functions
  void tankDriveVelocity(double leftVelocity, double rightVelocity);
  void drive(double speed, double rotation);
  void tankDrive(double leftSpeed, double rightSpeed);
  void brakeRobot();
  Segment* generatePath();
  int getPathLength();
  void setTalBrakeMode(NeutralMode neutralMode);

  // Encoder functions
  void zeroEncoders();
  double getRawLeftEncoder();
  double getRawRightEncoder();
  double getDistanceTravelled();
  double getRightVelocity();
  double getLeftVelocity();
  void velocityPIDConfig();
  void setTalControlMode(ControlMode controlMode);

  void disablePID();

  // Gyro functions
  void resetYaw();
  double getYaw();

  // Colour Sensor functions
  bool getColourSensorState(ColourSensor sensor);
  shared_ptr<DigitalInput> getColourSensorReference(ColourSensor sensor);
  bool clsBackLeftDetected();
  bool clsMidLeftDetected();
  bool clsBackRightDetected();
  bool clsMidRightDetected();

  // Ultrasonic functions
  double getUlsDistance(UltrasonicSensor ultrasonic);
  bool isBayEmpty(UltrasonicSensor ultrasonicSensor);
  double positionPID(double distance);
  void pidPositionConfig();
//   void setPIDSetPoint();
//   void enablePID();
//   bool isAtPIDSetPoint();

};
