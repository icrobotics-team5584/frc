// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <frc/controller/PIDController.h>

#include "subsystems/SubTurret.h"
#include "subsystems/SubStorage.h"

class CmdShoot
    : public frc2::CommandHelper<frc2::CommandBase, CmdShoot> {
 public:
  CmdShoot(SubStorage* subStorage, SubTurret* subTurret);
  void Initialize() override;
  void Execute() override;
  void End(bool interrupted) override;
  bool IsFinished() override;

 private:
  //PARAMETERS//
  
  double StorageSpeed = 0.85;
  double FeederSpeed = 1;
  //////////////

  void StopEverythingAndPanic();

  SubTurret* _subTurret;
  SubStorage* _subStorage;
  
};
