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

void SubArm::Toggle()
{
  // Need to add an isEnabled function
}

void SubArm::Enable()
{
  pidArm.Enable();
}

void SubArm::Disable()
{
  pidArm.Disable();
}

void SubArm::SetSetpoint(double setpoint)
{
  pidArm.SetSetpoint(setpoint);
}

void SubArm::SetRelativeSetpoint(double setpoint)
{
  pidArm.SetSetpointRelative(setpoint);
}

double SubArm::getAngle()
{
  return pidArm.GetPosition();
}


// Put methods for controlling this subsystem
// here. Call these from Commands.
