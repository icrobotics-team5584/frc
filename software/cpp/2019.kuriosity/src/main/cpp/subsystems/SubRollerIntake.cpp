/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubRollerIntake.h"
#include "Robot.h"

SubRollerIntake::SubRollerIntake() 
: Subsystem("ExampleSubsystem") {
  _srxRoller = Robot::_robotMap->srxRollerIntake;
}

void SubRollerIntake::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void SubRollerIntake::RollerIn() {
  _srxRoller->Set(-inSpeed);
}

void SubRollerIntake::RollerOut() {
  _srxRoller->Set(-outSpeed);
}

void SubRollerIntake::Stop() {
    _srxRoller->Set(0.0);
}