/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubPanelAffector.h"
#include "Robot.h"

SubPanelAffector::SubPanelAffector() : Subsystem("SubPanelAffector") {
  solLeft = Robot::_robotMap->solPanelAffectorLeft;
  solRight = Robot::_robotMap->solPanelAffectorRight;

  Retract();
}

void SubPanelAffector::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void SubPanelAffector::Retract() {
  solLeft->Set(DoubleSolenoid::kForward);
  solRight->Set(DoubleSolenoid::kReverse);
}

void SubPanelAffector::Deploy() {
  solLeft->Set(DoubleSolenoid::kForward);
  solRight->Set(DoubleSolenoid::kForward);
}
