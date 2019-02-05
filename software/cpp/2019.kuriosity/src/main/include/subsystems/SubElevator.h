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
#include <iostream>

using namespace std;
using namespace frc;

class SubElevator : public frc::Subsystem {
 private:

  shared_ptr<WPI_TalonSRX> _srxElevatorMaster;
  double _axis5 = 0;
  double targetPositionRotations = 0.0;
  double elevatorUpSpeed = -0.3;
  double elevatorDownSpeed = 0.2;
  double PIDP = 0.0;
  double PIDI = 0.0;
  double PIDD = 0.0;
	int overrideSpeed = 0;

 public:
 
  SubElevator();
  void Periodic();
  void InitDefaultCommand() override;
  void ElevatorToPos(double rotations);
  void Override(std::shared_ptr<Joystick>);
  void PIDEnable();
  void PIDDisable();
  void EncoderReset();
  void Stop();
  void TestingUp();
  void TestingDown();
  void TestingStop();
  void TestingUpStop();
  void TestingPID();
  int GetEncoderPosition();
};
