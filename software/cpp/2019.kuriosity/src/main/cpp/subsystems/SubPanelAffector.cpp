/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubPanelAffector.h"
#include "Robot.h"

SubPanelAffector::SubPanelAffector() : Subsystem("SubPanelAffector") {
  solTopLeft = Robot::_robotMap->solPanelAffectorTopLeft;
  solTopRight = Robot::_robotMap->solPanelAffectorTopRight;
  solBottomLeft = Robot::_robotMap->solPanelAffectorBottomLeft;
  solBottomRight = Robot::_robotMap->solPanelAffectorBottomRight;

  Retract();
}

void SubPanelAffector::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void SubPanelAffector::Retract() {
  solTopLeft->Set(DoubleSolenoid::kReverse);
  solTopRight->Set(DoubleSolenoid::kReverse);
  solBottomLeft->Set(DoubleSolenoid::kReverse);
  solBottomRight->Set(DoubleSolenoid::kReverse);
}

void SubPanelAffector::Deploy() {
  solTopLeft->Set(DoubleSolenoid::kForward);
  solTopRight->Set(DoubleSolenoid::kForward);
  solBottomLeft->Set(DoubleSolenoid::kForward);
  solBottomRight->Set(DoubleSolenoid::kForward);
}
