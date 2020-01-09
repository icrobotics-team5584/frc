/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubIntake.h"
#include "RobotMap.h"
#include <frc/smartdashboard/SmartDashboard.h>

SubIntake::SubIntake() : Subsystem("ExampleSubsystem") {
  srxIntake.reset(new TalonSRX(kIntakeMotor));

  srxIntake->ConfigPeakCurrentLimit(0, 30); //(current limit, timeout)
	srxIntake->ConfigPeakCurrentDuration(350, 30); //(time over limit to trigger, timeout)
	srxIntake->ConfigContinuousCurrentLimit(0.01, 30); //(set current to, timeout)
	srxIntake->EnableCurrentLimit(true);

  frc::SmartDashboard::PutNumber("Intake Speed", 0);
}

void SubIntake::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void SubIntake::Intake() {
  srxIntake->Set(ControlMode::PercentOutput, _speed);
}

void SubIntake::Outtake() {
  srxIntake->Set(ControlMode::PercentOutput, -_speed);
}

void SubIntake::Stop() {
  srxIntake->Set(ControlMode::PercentOutput, 0);
}

void SubIntake::Periodic()
{
  frc::SmartDashboard::PutNumber("Intake Current", srxIntake->GetOutputCurrent());
  _speed = frc::SmartDashboard::GetNumber("Intake Speed", 0);
}