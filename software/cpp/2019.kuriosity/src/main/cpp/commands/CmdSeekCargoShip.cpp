/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdSeekCargoShip.h"
#include "Robot.h"
#include <iostream>

CmdSeekCargoShip::CmdSeekCargoShip() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void CmdSeekCargoShip::Initialize() {
  
}

// Called repeatedly when this Command is scheduled to run
void CmdSeekCargoShip::Execute() {
  //This is done so that you only need to change drivePower when changing speed. The drivePower default is 100%
  Robot::subDriveBase->drive(-drivePower, 0);
  Robot::subDriveBase->getRange();
  if (Robot::subDriveBase->frontHasReachedLine()) {
    frontClsDetected = true;
  }
  if (Robot::subDriveBase->midHasReachedLine()) {
    midClsDetected = true;
  }

  SmartDashboard::PutNumber("frontClsDetected", frontClsDetected);
  SmartDashboard::PutNumber("midClsDetected", midClsDetected);


  if (frontClsDetected) {
    drivePower = 0.8;
    midClsDetected = false;
  }
  if (midClsDetected) {
    drivePower = 0.3;
    frontClsDetected = false;
  }
}

// Make this return true when this Command no longer needs to run execute()
bool CmdSeekCargoShip::IsFinished() {
  return Robot::subDriveBase->isBayEmpty(); 
}

// Called once after isFinished returns true
void CmdSeekCargoShip::End() {
  SmartDashboard::PutBoolean("started running End()", true);
  frc::Timer timer;
  timer.Start();
   while(!Robot::subDriveBase->midHasReachedLine() or (!(timer.Get() > 0.5))) {
    Robot::subDriveBase->getRange();
    SmartDashboard::PutBoolean("started running backwards()", true);
    Robot::subDriveBase->drive(0.5, 0);

   }
  Robot::subDriveBase->drive(0,0);
  SmartDashboard::PutBoolean("finished running backwards()", true);

  //run put cargo in bay here
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdSeekCargoShip::Interrupted() {
  End();
}
