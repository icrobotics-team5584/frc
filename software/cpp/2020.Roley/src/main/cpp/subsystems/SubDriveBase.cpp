/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubDriveBase.h"
#include "commands/CmdJoystickDrive.h"
#include "RobotMap.h"
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
  //enables the yaw to be reset
  ahrsNavXGyro->EnableBoardlevelYawReset(true);

  //_srxAutoXAxis.reset(new WPI_TalonSRX(can_srxDriveBaseAutoDolly));
  SubDriveBase::DiffDrive.reset(new frc::DifferentialDrive(*_srxFrontLeft, *_srxFrontRight));
  metersPerRotation = pi * WHEEL_DIAMETER;
}

void SubDriveBase::InitDefaultCommand() {

  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new CmdJoystickDrive());
}

void SubDriveBase::Periodic(){
  autoYaw = getActualYaw() - _targetYaw;
  SmartDashboard::PutNumber("autoyaw", autoYaw);

  SmartDashboard::PutNumber("yaw", ahrsNavXGyro->GetYaw());
  if(ahrsNavXGyro->IsCalibrating()){
    std::cout << "navx calibrating" << std::endl;
    
  }
}

void SubDriveBase::drive(double speed, double rotation, bool squaredInputs){
  frc::SmartDashboard::PutNumber("speed", speed);
  frc::SmartDashboard::PutNumber("rot", rotation);
  DiffDrive->ArcadeDrive(-speed, rotation, squaredInputs);
}

double SubDriveBase::getYaw(){
  return autoYaw;
}

double SubDriveBase::getActualYaw(){
  return ahrsNavXGyro->GetYaw();
}

void SubDriveBase::setTargetYaw(double targetYaw){
  _targetYaw = targetYaw;
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

void SubDriveBase::autoEncoderDrive(double target, double P, double I, double D, double Speed){
  //PID values and setting passed in from command
  kP = P;
  kI = I;
  kD = D;

  double error;
  double position;
  position = Robot::posEncoderGyro->getTempPositionX();//gets position from custom class located at "PosEncoderGyro.cpp"
  SmartDashboard::PutNumber("position", position);
  SmartDashboard::PutNumber("trench position", position + 1.7);


  //position - target is the error or "P"
  intergral = intergral + (position - target);//calculates total error or "I"
  //output = kP*theError         + kI*Intergral   + kD*Derivative
  error = kP*(position - target) + kI*(intergral) + kD*((position - target) - previousError);
  //error is the "steering" output of the PID
  previousError = position - target;//Calculates previous error for Derivative
  SmartDashboard::PutNumber("error", error);
  if (error < -1){//caps error at 1 and -1
    error = -1;
  }
  if (error > 1){
    error = 1;
  }
  //checks if the robot is over spinning and changes steering to zero. the derivative catches the robot at the line
  if((autoYaw < -50 && error < 0) || (autoYaw > 50 && error > 0)){
    error = 0;
  }
  SmartDashboard::PutNumber("error2", error);

  drive(Speed, error, false);//uses the same drive command as the joystick so onnly one can be run at the same time
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
