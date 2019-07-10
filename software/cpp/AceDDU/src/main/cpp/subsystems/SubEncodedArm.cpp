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

SubEncodedArm::SubEncodedArm() : Subsystem("ExampleSubsystem") {
  std::cout << "SubArm" << std::endl;
  srxArmFront.reset(new WPI_TalonSRX(3));
  srxArmBack.reset(new WPI_TalonSRX(1));
  std::cout << "SubArmTalon1" << std::endl;
	srxArmBack->Set(ControlMode::Follower, 3);
  std::cout << "SubArmTalons" << std::endl;

  srxArmFront->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute);
}

void SubEncodedArm::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
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

// Put methods for controlling this subsystem
// here. Call these from Commands.
