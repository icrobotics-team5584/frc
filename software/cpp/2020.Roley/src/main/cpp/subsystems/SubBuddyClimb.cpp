/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubBuddyClimb.h"
#include "commands/CmdBuddyDeploy.h"
#include <iostream>
#include "RobotMap.h"

SubBuddyClimb::SubBuddyClimb() : Subsystem("ExampleSubsystem") {
  SolRelease.reset(new frc::DoubleSolenoid(sol_buddyRight, sol_buddyLeft));
}

void SubBuddyClimb::InitDefaultCommand() {
  SetDefaultCommand(new CmdBuddyDeploy());
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void SubBuddyClimb::Reverse(){
  std::cout << "SubBuddyClimb reverse function called" << std::endl;
  SolRelease->Set(frc::DoubleSolenoid::kReverse);
}

void SubBuddyClimb::Forward(){
  std::cout << "SubBuddyClimb Forward function called" << std::endl;
  SolRelease->Set(frc::DoubleSolenoid::kForward);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

