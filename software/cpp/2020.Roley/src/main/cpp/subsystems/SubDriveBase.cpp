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
#include <cmath>

SubDriveBase::SubDriveBase() : Subsystem("ExampleSubsystem") {
  //motors
  _srxFrontLeft.reset(new WPI_TalonSRX(can_srxDriveBaseFrontLeft));
  _srxFrontRight.reset(new WPI_TalonSRX(can_srxDriveBaseFrontRight));
  _srxBackLeft.reset(new WPI_TalonSRX(can_srxDriveBaseBackLeft));
  _srxBackRight.reset(new WPI_TalonSRX(can_srxDriveBaseBackRight));
  _srxBackLeft->Follow(*_srxFrontLeft);
  _srxBackRight->Follow(*_srxFrontRight);

  solDollyAcuator.reset(new DoubleSolenoid(pcm_solDollyDeploy, pcm_solDollyRetract));

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
  //SmartDashboard::PutNumber("autoyaw", autoYaw);

  SmartDashboard::PutNumber("yaw", ahrsNavXGyro->GetYaw());
  //if(ahrsNavXGyro->IsCalibrating()){
  //  std::cout << "navx calibrating" << std::endl;
  //  
  //}

  //frc::SmartDashboard::PutString("cmd", GetCurrentCommandName());

}

void SubDriveBase::drive(double speed, double rotation, bool squaredInputs){
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

void SubDriveBase::autoEncoderDrive(double target, double P, double I, double D, double Speed, double TargetY){
  //PID values and setting passed in from command
  kP = P;
  kI = I;
  kD = D;

  double error;
  double position;
  position = Robot::posEncoderGyro->getTempPositionX();//gets position from custom class located at "PosEncoderGyro.cpp"
  SmartDashboard::PutNumber("position", position);


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

  y_position = Robot::posEncoderGyro->getTempPositionY();
  y_target = TargetY;
  y_intergral = y_intergral + (y_position - y_target);
  y_error = y_kP*(y_position - y_target) + y_kI*(y_intergral) + y_kD*((y_position - y_target) - y_previousError);
  y_previousError = y_position - y_target;

  SmartDashboard::PutNumber("y position", y_position);


  drive(y_error, error, false);//uses the same drive command as the joystick so onnly one can be run at the same time
  //std::cout << "auto stuff" << std::endl;
}

void SubDriveBase::resetYaw(){
  ahrsNavXGyro->ZeroYaw();
}

bool SubDriveBase::isNavxCal(){
  return ahrsNavXGyro->IsCalibrating();
}
// Put methods for controlling this subsystem
// here. Call these from Commands.


void SubDriveBase::deployDolly(){
  std::cout << "deploy dolly" << std::endl;
  solDollyAcuator->Set(frc::DoubleSolenoid::kForward);
}

void SubDriveBase::retractDolly(){
  std::cout << "retract dolly" << std::endl;
  solDollyAcuator->Set(frc::DoubleSolenoid::kReverse);
}

double SubDriveBase::getJoystickY(){
  if(abs(Robot::oi->getJoystickX()) < 0.2 && abs(Robot::oi->getJoystickY()) < 0.2){
    return -Robot::oi->getJoystick2Y();
  } else {
    return Robot::oi->getJoystickY();
  }
}

double SubDriveBase::getJoystickX(){
  if(abs(Robot::oi->getJoystickX()) < 0.2 && abs(Robot::oi->getJoystickY()) < 0.2){
    return Robot::oi->getJoystick2X();
  } else {
    return Robot::oi->getJoystickX();
  }
}