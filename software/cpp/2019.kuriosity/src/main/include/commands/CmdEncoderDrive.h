/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <frc/WPILib.h>
#include "pidControllers/PidsrcEncoderDrive.h"
#include "pidControllers/PidoutEncoderDrive.h"

class CmdEncoderDrive : public frc::Command {
 public:
  CmdEncoderDrive(double distance);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
private:
  std::unique_ptr<frc::PIDController> driveController;
  std::unique_ptr<PidsrcEncoderDrive> pidsrcEncoder;
  std::unique_ptr<PidoutEncoderDrive> pidoutEncoder;
  const double kP = 1.4;
  const double kI = 0;
  const double kD = 0;
};
