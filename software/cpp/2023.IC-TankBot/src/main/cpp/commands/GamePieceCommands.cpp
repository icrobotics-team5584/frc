// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/GamePieceCommands.h"
#include "subsystems/SubFlyWheel.h"
#include "subsystems/SubIndexer.h"

namespace cmd {
  using namespace frc2::cmd;


  frc2::CommandPtr StartFlyWheel() {
   return Run([] {SubFlyWheel::GetInstance().StartFlyWheel();});
  }

  frc2::CommandPtr StopFlyWheel() {
   return Run([] {SubFlyWheel::GetInstance().StopFlyWheel();});
  }

  frc2::CommandPtr StartIndexer() {
   return Run([] {SubIndexer::GetInstance().StartIndex();});
  }

  frc2::CommandPtr StopIndexer() {
   return Run([] {SubIndexer::GetInstance().StopIndex();});
  }

  frc2::CommandPtr StopShooting() {
   return Sequence(StopFlyWheel(), StopIndexer());
  }

  frc2::CommandPtr StartShooting() {
   return Sequence(StartFlyWheel(), Wait(0.5_s), StartIndexer(), Wait(0.2_s));
  }

  frc2::CommandPtr ShootBall() {
   return StartEnd(
    [] {StartShooting();},
    [] {StopShooting();}
    );
  }
}
