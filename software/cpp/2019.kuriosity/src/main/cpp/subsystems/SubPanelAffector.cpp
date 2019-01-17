/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubPanelAffector.h"
#include "Robot.h"
#include "commands/CmdOutputPanel.h"
#include "commands/CmdIntakePanel.h"

SubPanelAffector::SubPanelAffector() : Subsystem("SubPanelAffector") {
  solTop = Robot::_robotMap->solPanelAffectorTop;
  solBottom = Robot::_robotMap->solPanelAffectorBottom;
  solTopFinger = Robot::_robotMap->solPanelAffectorTopFinger;
  solBottomFinger = Robot::_robotMap->solPanelAffectorBottomFinger;
  SmartDashboard::PutData("Pneumatic Test", new CmdOutputPanel(true));

  Retract();
}

void SubPanelAffector::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void SubPanelAffector::Retract() {
  solTop->Set(DoubleSolenoid::kReverse);  
  //solBottom->Set(DoubleSolenoid::kReverse);
  
}

void SubPanelAffector::Deploy() {
  solTop->Set(DoubleSolenoid::kForward);
  //solBottom->Set(DoubleSolenoid::kForward);
}

void SubPanelAffector::DeployFingers() {
  solTopFinger->Set(DoubleSolenoid::kForward);
  solBottomFinger->Set(DoubleSolenoid::kForward);
}

void SubPanelAffector::RetractFingers() {
  solTopFinger->Set(DoubleSolenoid::kReverse);
  solBottomFinger->Set(DoubleSolenoid::kReverse);
}
