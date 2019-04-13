/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdSeekCargoShip.h"
#include "Robot.h"
#include <iostream>

CmdSeekCargoShip::CmdSeekCargoShip(ColourSensor colourSensor, UltrasonicSensor ultrasonicSensor) {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::subDriveBase.get());
  _colourSensor = colourSensor;
  _ultrasonicSensor = ultrasonicSensor;
}

// Called just before this Command runs the first time
void CmdSeekCargoShip::Initialize() {
  driveState = SEARCHING_FOR_SHIP;
  drivePower = 0.4;
}

// Called repeatedly when this Command is scheduled to run
void CmdSeekCargoShip::Execute() {
  //This is done so that you only need to change drivePower when changing speed. The drivePower default is 100%
    if (driveState == SEARCHING_FOR_SHIP) {
        if (Robot::subDriveBase->getColourSensorState(_colourSensor)) {
          drivePower = 0.4;
          driveState = AT_HATCH;
        }
    } 
    
    else if (driveState == AT_HATCH) {
        if (Robot::subDriveBase->isBayEmpty(_ultrasonicSensor)) {
          drivePower = 0;
          driveState = COMPLETE;
          timer.Start();    
        } 
        else {
          driveState = SEARCHING_FOR_SHIP;
        }
    }
  Robot::subDriveBase->drive(drivePower, 0);

}


// Make this return true when this Command no longer needs to run execute()
bool CmdSeekCargoShip::IsFinished() {
  return driveState == COMPLETE; 
}

// Called once after isFinished returns true
void CmdSeekCargoShip::End() {
//   Robot::subDriveBase->drive(0, 0);

  // SmartDashboard::PutBoolean("started running End()", true);
  //frc::Timer timer;
  //timer.Start();
  //while (timer.Get() < 0.25) {}
  //  while(!Robot::subDriveBase->midHasReachedLine() or (!(timer.Get() > 0.5))) {
  //   Robot::subDriveBase->getRange();
  //   SmartDashboard::PutBoolean("started running backwards()", true);
  //   Robot::subDriveBase->drive(-0.4, 0);
  //  }
   
  // Robot::subDriveBase->drive(0,0);
  // SmartDashboard::PutBoolean("finished running backwards()", true);

  //run put cargo in bay here
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdSeekCargoShip::Interrupted() {
  End();
}
