/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubStorage.h"
#include "RobotMap.h"

SubStorage::SubStorage() : Subsystem("ExampleSubsystem") {}

void SubStorage::InitDefaultCommand() {
  Motor.reset(new frc::VictorSP(pwn_Storage));
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void SubStorage::Forward(){
  Motor->Set(speed);
}

void SubStorage::Backward(){
  Motor->Set(-speed);
}

void SubStorage::Stop(){
  Motor->Set(0);
}




// Put methods for controlling this subsystem
// here. Call these from Commands.
