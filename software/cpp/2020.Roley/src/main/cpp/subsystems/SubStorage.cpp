/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubStorage.h"
#include "RobotMap.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "Robot.h"


SubStorage::SubStorage() : Subsystem("ExampleSubsystem") {
  srxStorage.reset(new TalonSRX(can_srxStorage));
  frc::SmartDashboard::PutNumber("Feeder speed", _speed);

  solStorageActuator.reset(new DoubleSolenoid(pcm_solStorageForward, pcm_solStorageRetract));

}

void SubStorage::InitDefaultCommand() {
  
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void SubStorage::Forward(){
  _speed = frc::SmartDashboard::GetNumber("Feeder speed", _speed);
  srxStorage->Set(ControlMode::PercentOutput, _speed);
}

void SubStorage::Backward(){
  _speed = frc::SmartDashboard::GetNumber("Feeder speed", _speed);
  srxStorage->Set(ControlMode::PercentOutput, -_speed);
}

void SubStorage::Stop(){
  srxStorage->Set(ControlMode::PercentOutput, 0);
}

void SubStorage::Expand(){
  solStorageActuator->Set(frc::DoubleSolenoid::kForward);
}

void SubStorage::Retract(){
  solStorageActuator->Set(frc::DoubleSolenoid::kReverse);
}


// Put methods for controlling this subsystem
// here. Call these from Commands.
