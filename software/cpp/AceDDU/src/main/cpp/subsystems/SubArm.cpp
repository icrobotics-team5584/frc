/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubArm.h"

SubArm::SubArm() : Subsystem("ExampleSubsystem") {}

void SubArm::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void SubArm::toggle()
{
  // Need to add an isEnabled function
}

void SubArm::enable()
{
  pidArm.Enable();
}

void SubArm::disable()
{
  pidArm.Disable();
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
