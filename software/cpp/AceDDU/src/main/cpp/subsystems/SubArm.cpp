/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubArm.h"

SubArm::SubArm() : Subsystem("SubArm") {
  srxShoulder.reset(new WPI_TalonSRX(5));

}

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

}

void SubArm::Disable()
{

}

void SubArm::SetSetpoint(double setpoint)
{

}

void SubArm::SetRelativeSetpoint(double setpoint)
{

}

double SubArm::getAngle()
{

}


// Put methods for controlling this subsystem
// here. Call these from Commands.