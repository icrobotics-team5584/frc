/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubElevator.h"
#include "Robot.h"

SubElevator::SubElevator() : Subsystem("ExampleSubsystem") {
  _srxElevator = Robot::_robotMap->srxElevator;
  _subElevatorLimitBottom = Robot::_robotMap->subElevatorLimitBottom;
  _subElevatorLimitTop = Robot::_robotMap->subElevatorLimitTop;
}

void SubElevator::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
