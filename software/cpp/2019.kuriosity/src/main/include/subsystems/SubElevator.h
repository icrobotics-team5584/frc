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
#include <AHRS.h>

using namespace std;
using namespace frc;

class SubElevator : public frc::Subsystem {
 private:

  shared_ptr<WPI_TalonSRX> _srxElevatorMaster;
  double _axis5 = 0;
  double targetPositionRotations;
  double elevatorUpSpeed = -0.3;
  double elevatorDownSpeed = 0.2;
	int overrideSpeed = 0;

 public:
 
  SubElevator();
  void InitDefaultCommand() override;
  void ElevatorToPos(double rotations);
  void Override(std::shared_ptr<Joystick>);
  void Stop();
  void TestingUp();
  void TestingDown();
  void TestingStop();
  void TestingUpStop();
  int GetEncoderPosition();
};
