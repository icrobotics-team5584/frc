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

  frc::SmartDashboard::PutNumber("Percent", 0);

  // leftMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, kTimeoutMs);
  // leftMotor->SetSensorPhase(true);
  // rightMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, kTimeoutMs);
  // rightMotor->SetSensorPhase(true);

  // leftMotor->ConfigNominalOutputForward(0, kTimeoutMs);
  // leftMotor->ConfigNominalOutputReverse(0, kTimeoutMs);
  // leftMotor->ConfigPeakOutputForward(1, kTimeoutMs);
  // leftMotor->ConfigPeakOutputReverse(-1, kTimeoutMs);

  // rightMotor->ConfigNominalOutputForward(0, kTimeoutMs);
	// rightMotor->ConfigNominalOutputReverse(0, kTimeoutMs);
	// rightMotor->ConfigPeakOutputForward(1, kTimeoutMs);
	// rightMotor->ConfigPeakOutputReverse(-1, kTimeoutMs);

  // frc::SmartDashboard::PutNumber("P Value", SetP);
  // frc::SmartDashboard::PutNumber("I Value", SetI);
  // frc::SmartDashboard::PutNumber("D Value", SetD);
  // frc::SmartDashboard::PutNumber("F Value", SetF);
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



void SubShooter::Shoot(){

    std::cout << "Shoot function running." << std::endl;

    percentage = frc::SmartDashboard::GetNumber("Percent", 0);

    // SetP = frc::SmartDashboard::GetNumber("P Value", 0);
    // SetI = frc::SmartDashboard::GetNumber("I Value", 0);
    // SetD = frc::SmartDashboard::GetNumber("D Value", 0);
    // SetF = frc::SmartDashboard::GetNumber("F Value", 0);

    // std::cout << "PID: " << SetP << ", " << SetI << ", " << SetD << ", " << SetF << std::endl;

    // leftMotor->Config_kF(kPIDLoopIdx, 0.0, kTimeoutMs);
    // leftMotor->Config_kP(kPIDLoopIdx, SetP, kTimeoutMs);
    // leftMotor->Config_kI(kPIDLoopIdx, SetI, kTimeoutMs);
    // leftMotor->Config_kD(kPIDLoopIdx, SetD, kTimeoutMs);

    // rightMotor->Config_kF(kPIDLoopIdx, 0.0, kTimeoutMs);
    // rightMotor->Config_kP(kPIDLoopIdx, SetP, kTimeoutMs);
    // rightMotor->Config_kI(kPIDLoopIdx, SetI, kTimeoutMs);
    // rightMotor->Config_kD(kPIDLoopIdx, SetD, kTimeoutMs);

    // double targetVelocity_UnitsPer100ms = RPM * 4096 / 600;

    // leftMotor->Set(ControlMode::Velocity, targetVelocity_UnitsPer100ms); 
    // rightMotor->Set(ControlMode::Velocity, -targetVelocity_UnitsPer100ms);

    leftMotor->Set(ControlMode::PercentOutput, percentage); 
    rightMotor->Set(ControlMode::PercentOutput, -percentage);

}

void SubShooter::Stop(){
  leftMotor->Set(0);
  rightMotor->Set(0);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
