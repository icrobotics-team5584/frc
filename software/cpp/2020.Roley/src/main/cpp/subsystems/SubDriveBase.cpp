/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubDriveBase.h"


SubDriveBase::SubDriveBase() : Subsystem("ExampleSubsystem") {
  //motors
  _srxFrontLeft.reset(new WPI_TalonSRX(can_srxDriveBaseFrontLeft));
  _srxFrontRight.reset(new WPI_TalonSRX(can_srxDriveBaseFrontRight));
  _srxBackLeft.reset(new WPI_TalonSRX(can_srxDriveBaseBackLeft));
  _srxBackRight.reset(new WPI_TalonSRX(can_srxDriveBaseBackRight));
  _srxBackLeft->Follow(*_srxFrontLeft);
  _srxBackRight->Follow(*_srxFrontRight);

  SubDriveBase::DiffDrive.reset(new frc::DifferentialDrive(*_srxFrontLeft, *_srxFrontRight));
}

void SubDriveBase::InitDefaultCommand() {

  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  //SetDefaultCommand(new CmdJoystickDrive());
}

void SubDriveBase::drive(double speed, double rotation){
  frc::SmartDashboard::PutNumber("speed", speed);
  frc::SmartDashboard::PutNumber("rot", rotation);
  DiffDrive->ArcadeDrive(speed, rotation);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
