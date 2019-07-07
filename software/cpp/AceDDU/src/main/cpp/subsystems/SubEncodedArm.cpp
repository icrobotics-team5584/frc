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
  srxArmFront.reset(new WPI_TalonSRX(3));
  srxArmBack.reset(new WPI_TalonSRX(1));

	srxArmBack->Set(ControlMode::Follower, 3);

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

int SubEncodedArm::getEncoder()
{
  return srxArmFront->GetSelectedSensorPosition(0);
}

double SubEncodedArm::getAngle()
{
  _angle = getEncoder() - _top;

  frc::SmartDashboard::PutNumber("Ticks to Top", _angle);
  
  _angleDeg = (_angle / 4096) * 360;

  frc::SmartDashboard::PutNumber("Actual Arm Angle", _angleDeg);

  return _angleDeg;
}

void SubEncodedArm::setSpeed(double speed)
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
