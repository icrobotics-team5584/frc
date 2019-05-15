/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdAutoDrive.h"
#include <Robot.h>
#include <frc/WPILib.h>
#include <iostream>


CmdAutoDrive::CmdAutoDrive(double distance) : distanceController(-4, 0, 0, &pidsrcDistance, &pidOutDistance)
{
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  _distance = distance;
}

// Called just before this Command runs the first time
void CmdAutoDrive::Initialize()
{
  Robot::subDrivebase->resetEncoders();
  frc::SmartDashboard::PutData("Distance Controller", &distanceController);
  distanceController.SetContinuous(false);
  distanceController.SetOutputRange(-0.5, 0.5);
  distanceController.SetSetpoint(_distance);
  distanceController.SetAbsoluteTolerance(0.05);
  distanceController.Enable();
}

// Called repeatedly when this Command is scheduled to run
void CmdAutoDrive::Execute() {
  
}

// Make this return true when this Command no longer needs to run execute()
bool CmdAutoDrive::IsFinished()
{
  if (distanceController.OnTarget())
  {
    return true;
  }

  else
  {
    return false;
  }
}

// Called once after isFinished returns true
void CmdAutoDrive::End()
{
  distanceController.Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdAutoDrive::Interrupted()
{
  End();
}