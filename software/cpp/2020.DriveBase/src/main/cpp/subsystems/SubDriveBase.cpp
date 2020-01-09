/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubDriveBase.h"
#include "commands/CmdDrive.h"

SubDriveBase::SubDriveBase() : Subsystem("SubDrivebBase") 
{
  //Talon

  _srxFrontLeft.reset(new WPI_TalonSRX(1));
  _srxFrontRight.reset(new WPI_TalonSRX(3));
  _srxBackLeft.reset(new WPI_TalonSRX(2));
  _srxBackRight.reset(new WPI_TalonSRX(4));
  _srxBackLeft->Follow(*_srxFrontLeft);
  _srxBackRight->Follow(*_srxFrontRight);

  //Diff Drive

  SubDriveBase::DiffDrive.reset(new frc::DifferentialDrive(*_srxFrontLeft, *_srxFrontRight));
}

void SubDriveBase::InitDefaultCommand() {

  // Set the default command for a subsystem here.
  SetDefaultCommand(new CmdDrive());
}



// Put methods for controlling this subsystem
// here. Call these from Commands.



//Drive

void SubDriveBase::Drive(double speed, double rotation){
  frc::SmartDashboard::PutNumber("speed", speed);
  frc::SmartDashboard::PutNumber("rot", rotation);
  DiffDrive->ArcadeDrive(speed, rotation);
}