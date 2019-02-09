/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubIntakeOutake.h"
#include "Robot.h"

SubIntakeOutake::SubIntakeOutake() 
: Subsystem("ExampleSubsystem") {
  _srxIntakeOutake = Robot::_robotMap->srxIntakeOutake;
  _dinCargoLimit = Robot::_robotMap->subIntakeOutakeCargo;
}

void SubIntakeOutake::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void SubIntakeOutake::Intake() {
  _srxIntakeOutake->Set(inSpeed);
}
void SubIntakeOutake::Outake() {
  _srxIntakeOutake->Set(outSpeed);
}
void SubIntakeOutake::Stop() {
  _srxIntakeOutake->Set(0.0);
}

bool SubIntakeOutake::GetCargoLimitSwitch() {
  return _dinCargoLimit->Get();
}