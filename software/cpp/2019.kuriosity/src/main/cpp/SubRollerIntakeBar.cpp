/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubRollerIntakeBar.h"
#include "Robot.h"

SubRollerIntakeBar::SubRollerIntakeBar() : Subsystem("ExampleSubsystem") {
  // Set PID constants
  const double kP = 0;
  const double kI = 0;
  const double kD = 0;
  
  srxRollerBar = Robot::_robotMap->srxRollerIntakeBar;

  // Set up PIDController
  pidsrcRoller.reset(new PidsrcRoller());
  pidoutRoller.reset(new PidoutRoller());
  positionController.reset(new PIDController(kP, kI, kD, pidsrcRoller.get(), pidoutRoller.get()));
}

void SubRollerIntakeBar::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

/*
 * 
 */
void SubRollerIntakeBar::SetPIDEnabled(bool enabled) {
  positionController->SetEnabled(enabled);
}

/*
 * 
 */
void SubRollerIntakeBar::SetSetpoint(double angle) {
  positionController->SetSetpoint(angle);
}

/*
 * 
 */
void SubRollerIntakeBar::SetSetpoint(RollerPosition rollerPosition) {
  switch (rollerPosition) {
    case OUT:
      SetSetpoint(0);
      break;
    case UP:
      SetSetpoint(90);
      break;
    case IN:
      SetSetpoint(120);
      break;
  }
}

/*
 * 
 */
double SubRollerIntakeBar::GetAngle() {
  return srxRollerBar->GetSelectedSensorPosition(0);
}

/*
 * 
 */
void SubRollerIntakeBar::MoveBar(double power) {
  srxRollerBar->Set(power);
}
