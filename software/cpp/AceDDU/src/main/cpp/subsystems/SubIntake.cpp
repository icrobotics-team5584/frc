/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubIntake.h"
#include "frc/WPILib.h"
#include "Robot.h"

bool is_cargo_mode = false;

SubIntake::SubIntake() : Subsystem("ExampleSubsystem") {
  SolMode.reset(new frc::DoubleSolenoid(2, 3));
  Motor.reset(new WPI_TalonSRX(1));

  Motor->ConfigPeakCurrentLimit(12, 30); //(current limit, timeout)
	Motor->ConfigPeakCurrentDuration(350, 30); //(time over limit to trigger, timeout)
	Motor->ConfigContinuousCurrentLimit(0.7, 30); //(set current to, timeout)
	Motor->EnableCurrentLimit(true);

}

void SubIntake::InitDefaultCommand() {
  
}

void SubIntake::Intake(){
  if(is_cargo_mode)
    Motor -> Set(SPEED);
  else
    Motor -> Set(-SPEED);
}

void SubIntake::Outtake(){
  if(is_cargo_mode)
    Motor -> Set(-SPEED);
  else
    Motor -> Set(SPEED);
}

void SubIntake::Stop(){
  Motor -> Set(0);
}

void SubIntake::CargoMode(){
  SolMode -> Set(frc::DoubleSolenoid::kForward);
  is_cargo_mode = true;
}

void SubIntake::HatchMode(){
  SolMode -> Set(frc::DoubleSolenoid::kReverse);
  is_cargo_mode = false;
}
