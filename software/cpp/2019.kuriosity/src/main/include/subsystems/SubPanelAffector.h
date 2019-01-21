/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>

using namespace std;
using namespace frc;

class SubPanelAffector : public frc::Subsystem {
 private:
  shared_ptr<DoubleSolenoid> solTop; 
  shared_ptr<DoubleSolenoid> solBottom;
  shared_ptr<DoubleSolenoid> solTopFinger;
  shared_ptr<DoubleSolenoid> solBottomFinger;

 public:
  SubPanelAffector();
  void InitDefaultCommand() override;
  void Retract();
  void Deploy();
  void DeployFingers();
  void RetractFingers();
};
