/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdSeekCargoShipRight.h"
#include "commands/CmdSeekCargoShip.h"
#include "commands/CmdEncoderDrive.h"
#include "commands/CmdGimbleRotateLeft.h"
#include "commands/CmdIntakeOutakeIn.h"
#include "subsystems/SubDriveBase.h"
CmdSeekCargoShipRight::CmdSeekCargoShipRight() {
  
  //AddSequential(new CmdGimbleRotateLeft());
  AddSequential(new CmdSeekCargoShip(ColourSensor::BACK_RIGHT, UltrasonicSensor::RIGHT));
  AddSequential(new CmdEncoderDrive(-0.26));
  AddSequential(new CmdIntakeOutakeIn());

}
