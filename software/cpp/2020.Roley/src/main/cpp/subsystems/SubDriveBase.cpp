/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubDriveBase.h"
#include "commands/CmdJoystickDrive.h"
#include "Robot.h"
SubDriveBase::SubDriveBase() : Subsystem("ExampleSubsystem") {
  //motors
  _srxFrontLeft.reset(new WPI_TalonSRX(can_srxDriveBaseFrontLeft));
  _srxFrontRight.reset(new WPI_TalonSRX(can_srxDriveBaseFrontRight));
  _srxBackLeft.reset(new WPI_TalonSRX(can_srxDriveBaseBackLeft));
  _srxBackRight.reset(new WPI_TalonSRX(can_srxDriveBaseBackRight));
  _srxBackLeft->Follow(*_srxFrontLeft);
  _srxBackRight->Follow(*_srxFrontRight);
  ahrsNavXGyro.reset(new AHRS(SPI::kMXP));
  _srxAutoXAxis.reset(new WPI_TalonSRX(can_srxDriveBaseAutoDolly));
  SubDriveBase::DiffDrive.reset(new frc::DifferentialDrive(*_srxFrontLeft, *_srxFrontRight));
  metersPerRotation = pi * WHEEL_DIAMETER;
}

void SubDriveBase::InitDefaultCommand() {

  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new CmdJoystickDrive());
}

void SubDriveBase::Periodic(){
  SmartDashboard::PutNumber("yaw", ahrsNavXGyro->GetYaw());
  if(ahrsNavXGyro->IsCalibrating()){
    std::cout << "navx calibrating" << std::endl;
  };
}

void SubDriveBase::drive(double speed, double rotation, bool squaredInputs){
  frc::SmartDashboard::PutNumber("speed", speed);
  frc::SmartDashboard::PutNumber("rot", rotation);
  DiffDrive->ArcadeDrive(speed, rotation, squaredInputs);
}

double SubDriveBase::getYaw(){
  return ahrsNavXGyro->GetYaw();
}

void SubDriveBase::zeroEncoders(){
  _srxFrontLeft->SetSelectedSensorPosition(0, 0);
  _srxFrontRight->SetSelectedSensorPosition(0, 0);
  _srxBackRight->SetSelectedSensorPosition(0, 0);
}

double SubDriveBase::getDistanceTravelled(){
  double encoderTics = _srxBackRight->GetSelectedSensorPosition(0);
  double wheelRotations = encoderTics / ENCODER_TICS_PER_ROTATION;
  double distance = wheelRotations * metersPerRotation;
  return distance;  
}

void SubDriveBase::autoEncoderDrive(double target){
  double error;
  double position;
  position = Robot::posEncoderGyro->getPositionx();
  SmartDashboard::PutNumber("position", position);
  intergral = intergral + (position - target);
  error = Kp*(position - target) + Ki*(intergral) + Kd*((position - target) - previousError);
  previousError = position - target;
  SmartDashboard::PutNumber("error", error);
  if (error < -1){
    error = -1;
  }
  if (error > 1){
    error = 1;
  }
  //if(ahrsNavXGyro->GetYaw() > 90 || ahrsNavXGyro->GetYaw() < -90){
  //  error = 0;
  //}
  SmartDashboard::PutNumber("error2", error);

  drive(AutoSpeed, error, false);
  std::cout << "auto stuff" << std::endl;
}

void SubDriveBase::resetYaw(){
  ahrsNavXGyro->ZeroYaw();
}

bool SubDriveBase::isNavxCal(){
  return ahrsNavXGyro->IsCalibrating();
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
