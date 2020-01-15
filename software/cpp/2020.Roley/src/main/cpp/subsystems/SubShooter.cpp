/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubShooter.h"
#include "RobotMap.h"
#include "frc/smartdashboard/SmartDashboard.h"

SubShooter::SubShooter() : Subsystem("ExampleSubsystem") {
  leftMotor.reset(new WPI_TalonSRX(can_srxShooterLeft));
  rightMotor.reset(new WPI_TalonSRX(can_srxShooterRight));

  leftMotor->ConfigFactoryDefault();
  rightMotor->ConfigFactoryDefault();

  leftMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, kTimeoutMs);
  rightMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, kTimeoutMs);

  leftMotor->ConfigNominalOutputForward(0, kTimeoutMs);
  leftMotor->ConfigNominalOutputReverse(0, kTimeoutMs);
  leftMotor->ConfigPeakOutputForward(1, kTimeoutMs);
  leftMotor->ConfigPeakOutputReverse(-1, kTimeoutMs);

  rightMotor->ConfigNominalOutputForward(0, kTimeoutMs);
	rightMotor->ConfigNominalOutputReverse(0, kTimeoutMs);
	rightMotor->ConfigPeakOutputForward(1, kTimeoutMs);
	rightMotor->ConfigPeakOutputReverse(-1, kTimeoutMs);

  leftMotor->Config_kF(kPIDLoopIdx, 0.1079, kTimeoutMs);
	leftMotor->Config_kP(kPIDLoopIdx, 0.22, kTimeoutMs);
	leftMotor->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
	leftMotor->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);

  rightMotor->Config_kF(kPIDLoopIdx, 0.1079, kTimeoutMs);
	rightMotor->Config_kP(kPIDLoopIdx, 0.22, kTimeoutMs);
	rightMotor->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
	rightMotor->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);
}

void SubShooter::InitDefaultCommand() {



  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}
double SubShooter::GetLeftRPM(){
  double sensorUnitVel = leftMotor->GetSelectedSensorVelocity();
  return sensorUnitVel/4096*600;
  
}

double SubShooter::GetRightRPM(){
  double sensorUnitVel = rightMotor->GetSelectedSensorVelocity();
  return sensorUnitVel/4096*600;
  
}



void SubShooter::Shoot(double RPM){
    double targetVelocity_UnitsPer100ms = RPM * 4096 / 600  ;
    leftMotor->Set(ControlMode::Velocity, targetVelocity_UnitsPer100ms); 
    rightMotor->Set(ControlMode::Velocity, -targetVelocity_UnitsPer100ms);
}

void SubShooter::Stop(){
  leftMotor->Set(0);
  rightMotor->Set(0);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
