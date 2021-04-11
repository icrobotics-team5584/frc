// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/controller/PIDController.h>
#include <frc/Timer.h>

#include "subsystems/SubStorage.h"
#include "subsystems/SubIntake.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class CmdIntake
    : public frc2::CommandHelper<frc2::CommandBase, CmdIntake> {
 public:
  CmdIntake(SubIntake* subIntake);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  SubStorage* _subStorage;
  SubIntake* _subIntake;

  double StorageP = 0.00006;
  double StorageI = 0.0;
  double StorageD = 0.0;
  double StorageF = 0.85;

  frc2::PIDController _storagePID{StorageP, StorageI, StorageD};
  frc::Timer _timer;
  frc::Timer _overcurrenttime;
  frc::Timer _delayIntake;
  SubStorage::Direction _currentdir = SubStorage::Direction::Forward;
  double Setpoint = 10000;

};
