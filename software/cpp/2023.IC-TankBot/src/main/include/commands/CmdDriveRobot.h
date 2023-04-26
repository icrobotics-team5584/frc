// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/XboxController.h>
#include <frc/filter/SlewRateLimiter.h>
#include <units/voltage.h>


/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class CmdDriveRobot
    : public frc2::CommandHelper<frc2::CommandBase, CmdDriveRobot> {
 public:
  CmdDriveRobot(frc::XboxController* controller);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  frc::XboxController* _XboxController;

  private:
  frc::SlewRateLimiter<units::volts> _stickYLimiter{2_V / 1_s};

};
