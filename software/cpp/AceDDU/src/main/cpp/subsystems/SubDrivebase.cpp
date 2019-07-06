/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubDrivebase.h"
#include "Commands/CmdDrive.h"



void SubDrivebase::PIDWrite(double output){

  drive(0,output);
  

}

SubDrivebase::SubDrivebase() : Subsystem("ExampleSubsystem") {
std::cout << "SubDriveBaseStart" << std::endl;
//motors
srxFrontLeft.reset(new WPI_TalonSRX(100));      //2
srxFrontRight.reset(new WPI_TalonSRX(110));     //1
srxBackLeft.reset(new WPI_TalonSRX(120));       //4
srxBackRight.reset(new WPI_TalonSRX(130));      //3
srxBackLeft->Set(ControlMode::Follower, 100);   //2
srxBackRight->Set(ControlMode::Follower, 110);  //1

//drive
diffdrive.reset(new frc::DifferentialDrive(*srxFrontLeft,*srxFrontRight));

//sensors
imu.reset(new PigeonIMU(srxFrontRight.get()));

//global variables? can this be moved to the header file?
circumference = PI * WHEEL_DIAMETER;
std::cout << "SubDriveBaseEnd" << std::endl;
}



void SubDrivebase::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new CmdDrive());



}

// Put methods for controlling this subsystem

void SubDrivebase::drive(double speed, double rotation){

  frc::SmartDashboard::PutNumber("Rotation out", rotation);
  frc::SmartDashboard::PutNumber("speed out", speed);
  //diffdrive->ArcadeDrive(speed, rotation); //RObot Driving

  


}
// here. Call these from Commands.

int SubDrivebase::get_angle(){
  unsigned int ang=360;

  return (int)imu->GetFusedHeading()%ang -180;


}


int SubDrivebase::get_RightEncoder(){
  return srxBackRight->GetSelectedSensorPosition(0); //index 0



}

int SubDrivebase::get_LeftEncoder(){
  return srxBackLeft->GetSelectedSensorPosition(0); //index 0
}

  /*
  Left = talon 3
  Right = talon 4
  */

double SubDrivebase::get_distance(){
  double avrage{0}; 
  avrage = (-get_RightEncoder() + get_LeftEncoder()) / 2;
  double rotation{0};
  rotation = avrage / 4096;
  double distance;
  distance = rotation * circumference;
  return distance;
  srxBackLeft->SetSelectedSensorPosition(0);
  srxBackRight->SetSelectedSensorPosition(0);
      
}

void SubDrivebase::resetEncoders(){
  srxBackLeft->SetSelectedSensorPosition(0);
  srxBackRight->SetSelectedSensorPosition(0);
}


