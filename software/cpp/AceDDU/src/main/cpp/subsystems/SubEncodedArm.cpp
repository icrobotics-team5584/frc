/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubEncodedArm.h"
#include <frc/commands/Subsystem.h>
#include "frc/WPILib.h"
#include <ctre/phoenix.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include <iostream>

SubEncodedArm::SubEncodedArm() : Subsystem("ExampleSubsystem") {
  srxArmFront.reset(new WPI_TalonSRX(3));
	srxArmBack->Set(ControlMode::Follower, 1);
}

void SubEncodedArm::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

int SubEncodedArm::getEncoder()
{
  return srxArmBack->GetSelectedSensorPosition(0);
}

void SubEncodedArm::setSpeed(double speed)
{
  srxArmFront->Set(speed);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
