/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdAngleTurn.h"
#include <Robot.h>

CmdAngleTurn::CmdAngleTurn(double angle) : angleController(-0.05, 0, 0, &pidsrcAngle, Robot::subDrivebase.get())
{
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subDrivebase.get());
  _angle = angle;
}

// Called just before this Command runs the first time
void CmdAngleTurn::Initialize()
{
  frc::SmartDashboard::PutData("angle controler", &angleController);
  angleController.SetContinuous(true);
  angleController.SetInputRange(-180, 180);
  angleController.SetOutputRange(-0.5, 0.5);
  angleController.SetSetpoint(_angle);
  angleController.SetAbsoluteTolerance(5);
  angleController.Enable();
}

// Called repeatedly when this Command is scheduled to run
void CmdAngleTurn::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdAngleTurn::IsFinished()
{
  if (angleController.OnTarget())
  {
    return true;
  }

  else
  {
    return false;
  }
}

// Called once after isFinished returns true
void CmdAngleTurn::End()
{
  angleController.Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdAngleTurn::Interrupted()
{
  End();
}
