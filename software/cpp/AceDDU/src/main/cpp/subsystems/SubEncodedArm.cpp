/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubEncodedArm.h"
#include <frc/commands/Subsystem.h>
#include "frc/WPILib.h"
#include <ctre/phoenix.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include <iostream>
#include "commands/CmdIdleArm.h"

SubEncodedArm::SubEncodedArm() : Subsystem("ExampleSubsystem") {

  //motors
  srxArmFront.reset(new WPI_TalonSRX(2));
  srxArmBack.reset(new WPI_TalonSRX(3));

  srxArmFront->ConfigFactoryDefault();
  srxArmBack->ConfigFactoryDefault();

	srxArmBack->Set(ControlMode::Follower, 2);

  //sensors
  srxArmFront->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute);

  //pneumatics
  pneuBrake.reset(new frc::DoubleSolenoid(2,3));
}

void SubEncodedArm::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new CmdIdleArm());
}

void SubEncodedArm::ConfigTalon(){
  // Configure Talon SRX
  // Set the frame periods. It seems like we need this or maybe not but it's here in case.
  

  srxArmFront->SetStatusFramePeriod(StatusFrameEnhanced::Status_13_Base_PIDF0, 10, 10);
  srxArmFront->SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 10, 10);

  // Set peak outputs
  srxArmFront->ConfigPeakOutputForward(0.6, 0);
  srxArmFront->ConfigPeakOutputReverse(-0.6, 0);
  
  //set feedfoward
  position = Robot::subEncodedArm->getEncoder();
  angleRadians = Robot::subEncodedArm->getAngle() * (3.14/180);
  kF = 0.2 * 1023;

  // Set motion magic gains **These numbers aren't set right yet (for muck)**
  srxArmFront->SelectProfileSlot(0, 0);
  srxArmFront->Config_kF(0, kF, 0);
  srxArmFront->Config_kP(0, 0.1, 0);
  srxArmFront->Config_kI(0, 0, 0);
  srxArmFront->Config_kD(0, 0, 0);

  // Set acceleration and cruise velocity
  srxArmFront->ConfigMotionCruiseVelocity(300, 0);
  srxArmFront->ConfigMotionAcceleration(300, 0);
}
int SubEncodedArm::getEncoder()
{
  return srxArmFront->GetSelectedSensorPosition(0);
}

double SubEncodedArm::getAngle()
{
  _angle = getEncoder();

  frc::SmartDashboard::PutNumber("Ticks to Top", _angle);
  
  _angleDeg = (_angle / 4096) * 360;

  frc::SmartDashboard::PutNumber("Actual Arm Angle", _angleDeg);

  return _angleDeg;
}

void SubEncodedArm::setSpeed(double speed) //Hardcodes power as %!!!!!
{
  srxArmFront->Set(speed);
  frc::SmartDashboard::PutNumber("Arm Speed", speed);
}

/*
* For one time use to put 0 degrees at the correct position.
*/
void SubEncodedArm::ResetEncoder() {
  srxArmFront->SetSelectedSensorPosition(0);
}

/*
* Changes the state of the arm's pneumatic braking system
*
* @param brakeState The desired state of the arm brake (brake, coast)
*/
void SubEncodedArm::BrakeState(PneuBrakeState brakeState) {
  switch(brakeState) {

    case(BRAKE) : pneuBrake->Set(frc::DoubleSolenoid::kForward);

    case(COAST) : pneuBrake->Set(frc::DoubleSolenoid::kReverse);
  }
}

/* Enables motion magic based off of a desired position
* @param desired angle of the arm
*/
void SubEncodedArm::SetPosition(double angle){
  
  angle = (angle / 360) * 4096;
  std::cout << "angle input: " <<  angle << std::endl;
  srxArmFront->Set(ControlMode::MotionMagic, angle);
}
