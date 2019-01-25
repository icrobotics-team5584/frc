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
#include "subsystems/PIDPot.h"
using namespace std;
using namespace frc;

class SubGimble : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  shared_ptr<frc::Talon> _talGimble; 
  shared_ptr<AnalogInput> _anaGimblePot;
  shared_ptr<DigitalInput> _LimitLeft;
  shared_ptr<DigitalInput> _LimitRight;
  double rotateSpeed = 0.5;
  PIDController* gimbleController;
  PIDPot* _potSourcePID;

  double PotLeft = 9999;
	double PotRight = 9999;
	double PotCentre = 9999;
	double PIDp = 0.0;
	double PIDi = 0.0;
	double PIDd = 0.0;
  int potRange;
  int target;
	int  lc = 0;
  int totalAngle = 180;


  public:
  SubGimble();
  void Periodic();
  void InitDefaultCommand() override;
  void rotateLeft();
  void rotateRight();
  void stop();
  void enable();
  void disable();
  void PIDGimbleTo(int angle);  
};
