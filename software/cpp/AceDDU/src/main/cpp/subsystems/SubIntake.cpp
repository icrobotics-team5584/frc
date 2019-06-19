/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubIntake.h"
#include "frc/WPILib.h"
#include "Robot.h"

SubIntake::SubIntake() : Subsystem("ExampleSubsystem") {
  SolMode.reset(new frc::DoubleSolenoid(1, 0));
  Motor.reset(new WPI_TalonSRX(5));
}

void SubIntake::InitDefaultCommand() {
  
}
void SubIntake::Intake(){
  Motor -> Set(SPEED);
}
void SubIntake::Outtake(){
  Motor -> Set(-SPEED);
}
void SubIntake::Stop(){
  Motor -> Set(0);
}
void SubIntake::CargoMode(){
  SolMode -> Set(frc::DoubleSolenoid::kForward);
}
void SubIntake::HatchMode(){
  SolMode -> Set(frc::DoubleSolenoid::kReverse);
}