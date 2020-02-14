/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

/*
  PID Control for this subsystem is currently set through SmartDashboard.
  Nothing is currently hard-coded, but at the moment I've found these values to work quite well:
  LEFT: P=0.034200, I=0, D=0, F=0.01
  RIGHT: P=0.034200, I=0, D=0, F=0.0115
*/

#include "subsystems/SubShooter.h"
#include "RobotMap.h"
#include "frc/smartdashboard/SmartDashboard.h"

SubShooter::SubShooter() : Subsystem("ExampleSubsystem") {
  leftMotor.reset(new WPI_TalonSRX(can_srxShooterLeft));
  rightMotor.reset(new WPI_TalonSRX(can_srxShooterRight));

  leftMotor->ConfigFactoryDefault();
  rightMotor->ConfigFactoryDefault();

  //frc::SmartDashboard::PutNumber("RPM", 0);

  leftMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, kTimeoutMs);
  leftMotor->SetSensorPhase(true);
  rightMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, kTimeoutMs);
  rightMotor->SetSensorPhase(true);

  leftMotor->ConfigNominalOutputForward(0, kTimeoutMs);
  leftMotor->ConfigNominalOutputReverse(0, kTimeoutMs);
  leftMotor->ConfigPeakOutputForward(1, kTimeoutMs);
  leftMotor->ConfigPeakOutputReverse(-1, kTimeoutMs);

  rightMotor->ConfigNominalOutputForward(0, kTimeoutMs);
	rightMotor->ConfigNominalOutputReverse(0, kTimeoutMs);
	rightMotor->ConfigPeakOutputForward(1, kTimeoutMs);
	rightMotor->ConfigPeakOutputReverse(-1, kTimeoutMs);

  leftMotor->SetNeutralMode(NeutralMode::Coast);
  rightMotor->SetNeutralMode(NeutralMode::Coast);

  // frc::SmartDashboard::PutNumber("P Value Left", SetPLeft);
  // frc::SmartDashboard::PutNumber("I Value Left", SetILeft);
  // frc::SmartDashboard::PutNumber("D Value Left", SetDLeft);
  // frc::SmartDashboard::PutNumber("F Value Left", SetFLeft);

  // frc::SmartDashboard::PutNumber("P Value Right", SetPRight);
  // frc::SmartDashboard::PutNumber("I Value Right", SetIRight);
  // frc::SmartDashboard::PutNumber("D Value Right", SetDRight);
  // frc::SmartDashboard::PutNumber("F Value Right", SetFRight);
  frc::SmartDashboard::PutNumber("Shooter Speed", shooterSpeed);
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

void SubShooter::PowerShoot(){
  shooterSpeed = frc::SmartDashboard::GetNumber("Shooter Speed", 0.8);
  leftMotor->Set(ControlMode::PercentOutput, -shooterSpeed);
  rightMotor->Set(ControlMode::PercentOutput, shooterSpeed);
}

void SubShooter::Shoot(){

    std::cout << "Shoot function running." << std::endl;

    // RPM = frc::SmartDashboard::GetNumber("RPM", 0);

    // SetPLeft = frc::SmartDashboard::GetNumber("P Value Left", 0);
    // SetILeft = frc::SmartDashboard::GetNumber("I Value Left", 0);
    // SetDLeft = frc::SmartDashboard::GetNumber("D Value Left", 0);
    // SetFLeft = frc::SmartDashboard::GetNumber("F Value Left", 0);

    // SetPRight = frc::SmartDashboard::GetNumber("P Value Right", 0);
    // SetIRight = frc::SmartDashboard::GetNumber("I Value Right", 0);
    // SetDRight = frc::SmartDashboard::GetNumber("D Value Right", 0);
    // SetFRight = frc::SmartDashboard::GetNumber("F Value Right", 0);

    // std::cout << "PID Left: " << SetPLeft << ", " << SetILeft << ", " << SetDLeft << ", " << SetFLeft << std::endl;
    // std::cout << "PID Right: " << SetPRight << ", " << SetIRight << ", " << SetDRight << ", " << SetFRight << std::endl;
    // std::cout << "Target RPM: " << RPM << std::endl;

    // leftMotor->Config_kF(kPIDLoopIdx, SetFLeft, kTimeoutMs);
    // leftMotor->Config_kP(kPIDLoopIdx, SetPLeft, kTimeoutMs);
    // leftMotor->Config_kI(kPIDLoopIdx, SetILeft, kTimeoutMs);
    // leftMotor->Config_kD(kPIDLoopIdx, SetDLeft, kTimeoutMs);

    // rightMotor->Config_kF(kPIDLoopIdx, SetFRight, kTimeoutMs);
    // rightMotor->Config_kP(kPIDLoopIdx, SetPRight, kTimeoutMs);
    // rightMotor->Config_kI(kPIDLoopIdx, SetIRight, kTimeoutMs);
    // rightMotor->Config_kD(kPIDLoopIdx, SetDRight, kTimeoutMs);

    // double targetVelocity_UnitsPer100ms = RPM * 4096 / 600;

    // std::cout << "targetVelocity_UnitsPer100ms: " << targetVelocity_UnitsPer100ms << std::endl;

    // leftMotor->Set(ControlMode::Velocity, targetVelocity_UnitsPer100ms); 
    // rightMotor->Set(ControlMode::Velocity, -targetVelocity_UnitsPer100ms);

    // leftMotor->Set(ControlMode::PercentOutput, percentage); 
    // rightMotor->Set(ControlMode::PercentOutput, -percentage);

}

void SubShooter::Stop(){
  leftMotor->Set(0);
  rightMotor->Set(0);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
