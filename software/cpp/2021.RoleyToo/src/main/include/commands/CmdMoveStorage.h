// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/controller/PIDController.h>
#include <frc/Timer.h>

#include "subsystems/SubStorage.h"

class CmdMoveStorage
    : public frc2::CommandHelper<frc2::CommandBase, CmdMoveStorage> {
 public:
  CmdMoveStorage(SubStorage* subStorage, int antiJamRPM = 0);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
 private:
    SubStorage* _subStorage;

    double StorageP = 0.00006;
    double StorageI = 0.0;
    double StorageD = 0.0;
    double StorageF = 0.85;

    frc2::PIDController _storagePID{StorageP, StorageI, StorageD};
    frc::Timer _timer;
    frc::Timer _overcurrenttime;
    SubStorage::Direction _currentdir = SubStorage::Direction::Forward;
    double Setpoint = 10000;
    double power = 0;

    double _antiJamRPM = 0;
};
