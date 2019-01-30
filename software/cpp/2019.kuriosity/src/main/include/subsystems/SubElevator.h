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
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  shared_ptr<WPI_TalonSRX> _srxElevatorMaster;
  shared_ptr<DigitalInput> _subElevatorLimitBottom;
  shared_ptr<DigitalInput> _subElevatorLimitTop;
  double targetPosRotations;
  double _axis5 = 0;
  double targetPositionRotations;
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
};
