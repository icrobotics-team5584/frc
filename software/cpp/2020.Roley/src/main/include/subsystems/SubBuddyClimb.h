/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>

#include <frc/DoubleSolenoid.h>


class SubBuddyClimb : public frc::Subsystem {
 private:
   std::shared_ptr<frc::DoubleSolenoid> SolRelease;
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

 public:
  SubBuddyClimb();
  void InitDefaultCommand() override;
  void Reverse();
  void Forward();
};
