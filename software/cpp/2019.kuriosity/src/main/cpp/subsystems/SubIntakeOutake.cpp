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
  _talLeft = Robot::_robotMap->talIntakeOutakeLeft;
  _talRight = Robot::_robotMap->talIntakeOutakeRight;
}

void SubIntakeOutake::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void SubIntakeOutake::Intake() {
  _talLeft->Set(-inSpeed);
  _talRight->Set(inSpeed);
}
void SubIntakeOutake::Outake() {
  _talLeft->Set(-outSpeed);
  _talRight->Set(outSpeed);
}
void SubIntakeOutake::Stop() {
  _talRight->Set(0.0);
  _talLeft->Set(0.0);

}