/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdPidArm.h"
#include <Robot.h>

CmdPidArm::CmdPidArm(double position) : armController(-0.05, 0, 0, &pidsrcArm, Robot::subDrivebase.get()/*replace with arm encoder*/)
{
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  srxShoulder.reset(new WPI_TalonSRX(5));
  _position = position;
}

// Called just before this Command runs the first time
void CmdPidArm::Initialize()
{
  frc::SmartDashboard::PutData("angle controler", &armController);
  armController.SetContinuous(false);
  armController.SetInputRange(-180, 180);
  armController.SetOutputRange(-0.5, 0.5);
  armController.SetSetpoint(_position);
  //armController.SetAbsoluteTolerance(5);
  armController.Enable();
}

// Called repeatedly when this Command is scheduled to run
void CmdPidArm::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdPidArm::IsFinished()
{
  if (armController.OnTarget())
  {
    return true;
  }

  else
  {
    return false;
  }
}

// Called once after isFinished returns true
void CmdPidArm::End()
{
  armController.Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdPidArm::Interrupted()
{
  End();
}
