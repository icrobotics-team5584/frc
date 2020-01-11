/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubShooter.h"
#include "RobotMap.h"
#include "frc/smartdashboard/SmartDashboard.h"

SubShooter::SubShooter() : Subsystem("ExampleSubsystem") {}

void SubShooter::InitDefaultCommand() {
  leftMotor.reset(new WPI_TalonSRX(can_srxShooterLeft));
  rightMotor.reset(new WPI_TalonSRX(can_srxShooterRight));

  leftMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);
  rightMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}
double SubShooter::GetLeftRPM(){
  double sensorUnitVel = leftMotor->GetSelectedSensorPosition();
  return sensorUnitVel/4096*600;
  
}

double SubShooter::GetRightRPM(){
  double sensorUnitVel = rightMotor->GetSelectedSensorPosition();
  return sensorUnitVel/4096*600;
  
}

void SubShooter::Periodic(){
  frc::SmartDashboard::PutNumber("Right RPM",GetRightRPM());
  frc::SmartDashboard::PutNumber("Left RPM", GetLeftRPM());
  speed = frc::SmartDashboard::GetNumber("Motor Speed", speed);
}


void SubShooter::Shoot(){
  leftMotor->Set(speed);
  rightMotor->Set(-speed);
}

void SubShooter::Stop(){
  leftMotor->Set(0);
  rightMotor->Set(-0);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
