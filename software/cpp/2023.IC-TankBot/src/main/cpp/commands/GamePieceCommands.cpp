// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/GamePieceCommands.h"
#include "subsystems/SubFlyWheel.h"
#include "subsystems/SubIndexer.h"

namespace cmd {
  using namespace frc2::cmd;


  frc2::CommandPtr StartFlyWheel() {
    Run([] {SubFlyWheel::GetInstance().StartFlyWheel();});
  }

  frc2::CommandPtr StopFlyWheel() {
    Run([] {SubFlyWheel::GetInstance().StopFlyWheel();});
  }

  frc2::CommandPtr StartIndexer() {
    Run([] {SubIndexer::GetInstance().StartIndex();});
  }

  frc2::CommandPtr StopIndexer() {
    Run([] {SubIndexer::GetInstance().StopIndex();});
  }

  frc2::CommandPtr StopShooting() {
    Sequence(StopFlyWheel(), StopIndexer());
  }

  frc2::CommandPtr StartShooting() {
    Sequence(StartFlyWheel(), Wait(2_s), StartIndexer(), Wait(0.2_s));
  }

  frc2::CommandPtr ShootBall() {
    StartEnd(
    [] {StartShooting();},
    [] {StopShooting();}
    );
  }
}
