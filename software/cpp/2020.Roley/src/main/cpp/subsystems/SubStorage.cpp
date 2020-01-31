/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubStorage.h"
#include "RobotMap.h"

SubStorage::SubStorage() : Subsystem("ExampleSubsystem") {
  srxStorage.reset(new TalonSRX(can_srxStorage));
}

void SubStorage::InitDefaultCommand() {
  
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void SubStorage::Forward(){
  srxStorage->Set(ControlMode::PercentOutput, speed);
}

void SubStorage::Backward(){
  srxStorage->Set(ControlMode::PercentOutput, -speed);
}

void SubStorage::Stop(){
  srxStorage->Set(ControlMode::PercentOutput, 0);
}




// Put methods for controlling this subsystem
// here. Call these from Commands.
