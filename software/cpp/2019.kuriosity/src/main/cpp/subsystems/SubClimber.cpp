/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubClimber.h"
#include "Robot.h"

SubClimber::SubClimber() : Subsystem("ExampleSubsystem") {}

void SubClimber::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  _spxClimber = Robot::_robotMap->spxClimber;
  _spxClimberSlave = Robot::_robotMap->spxClimberSlave;
  _spxClimberSlave->Set(ControlMode::Follower, _spxClimber->GetDeviceID());
  _srvLatch = Robot::_robotMap->srvClimberLatch;
  _limLimit = Robot::_robotMap->limClimberLimit;

  Stop();
}

// Put methods for controlling this subsystem
// here. Call these from Commands.


void SubClimber::Go(){
  _spxClimber->Set(ControlMode::PercentOutput, LIFT_POWER);
}


void SubClimber::Retract() {
  _spxClimber->Set(ControlMode::PercentOutput, RETRACT_POWER);
}


void SubClimber::Stop(){
  _spxClimber->Set(ControlMode::PercentOutput, STORE_POWER);
}


void SubClimber::Hold() {
  _spxClimber->Set(ControlMode::PercentOutput, HOLD_POWER);
}


void SubClimber::Latch() {
  _srvLatch->Set(LATCHED_POSITION);
}


void SubClimber::Unlatch() {
  _srvLatch->Set(UNLATCHED_POSITION);
}


bool SubClimber::IsLatched() {
  double error = _srvLatch->Get() - LATCHED_POSITION; 
  return (error < IS_LATCHED_TOLERANCE);
}


bool SubClimber::GetLimit() {
  return _limLimit->Get();
}