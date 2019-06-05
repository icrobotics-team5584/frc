/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubEncodedArm.h"
#include <Commands/Subsystem.h>
#include "WPILib.h"
#include <ctre/phoenix.h>
#include <SmartDashboard/SmartDashboard.h>
#include <iostream>

SubEncodedArm::SubEncodedArm() : Subsystem("ExampleSubsystem") {
  

  armController = new frc::PIDController(PIDp, PIDi, PIDd, _potSourcePID, _armOutputPID);
}



void SubEncodedArm::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
