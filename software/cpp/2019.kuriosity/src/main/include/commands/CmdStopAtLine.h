/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include "Robot.h"
#include "subsystems/SubDriveBase.h"
#include "subsystems/SubGimble.h"

class CmdStopAtLine : public frc::Command {
 public:
  CmdStopAtLine(double speed = 0.6);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
 
 private:
  frc::Counter leftLineCounter;
  frc::Counter rightLineCounter;

  ColourSensor _leftColourSensor;
  ColourSensor _rightColourSensor;
  
  double _speed;
  double frontClsDetected;
  double midClsDetected;
  bool finishStage;
  double initialEncoderPos;
  double distance;

  double initialAngle;
  double desiredAngle;
  double currentAngle;
  double kP = 0.05;
};
