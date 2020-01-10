/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubDriveBase.h"
#include "commands/CmdDrive.h"
#include "frc/SmartDashboard/SmartDashboard.h"


SubDriveBase::SubDriveBase() : Subsystem("SubDrivebBase")
{
  //Talon

  _srxFrontLeft.reset(new WPI_TalonSRX(1));
  _srxFrontRight.reset(new frc::VictorSP(3));
  _srxBackLeft.reset(new WPI_TalonSRX(2));
  _srxBackRight.reset(new frc::VictorSP(4));

  LeftGroup.reset(new frc::SpeedControllerGroup(*_srxBackLeft, *_srxFrontLeft));
  RightGroup.reset(new frc::SpeedControllerGroup(*_srxBackRight, *_srxFrontRight));
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