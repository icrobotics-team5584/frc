/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubClimber.h"
#include <frc/WPILib.h>
#include <iostream>
SubClimber::SubClimber() : Subsystem("ExampleSubsystem") {

  std::cout << "Climber Construct" << std::endl;
solClimber.reset(new frc::DoubleSolenoid(0, 1));

}
void SubClimber::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void SubClimber::VacuumIn() {
  std::cout << "Climber VacuumIn" << std::endl;
  solClimber->Set(frc::DoubleSolenoid::kForward);

}

void SubClimber::VacuumOut() {
  std::cout << "Climber VacuumOut" << std::endl;
  solClimber->Set(frc::DoubleSolenoid::kReverse);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
