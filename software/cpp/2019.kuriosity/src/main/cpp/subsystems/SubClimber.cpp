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
  _srxClimber = Robot::_robotMap->srxClimber;
}

// Put methods for controlling this subsystem
// here. Call these from Commands.


void SubClimber::Go(){
  _srxClimber->Set(0.25);
}
void SubClimber::Stop(){
  _srxClimber->Set(0.0);
}