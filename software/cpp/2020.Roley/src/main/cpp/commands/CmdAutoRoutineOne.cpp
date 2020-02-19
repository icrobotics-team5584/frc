/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdAutoRoutineOne.h"
#include "commands/CmdAutoEncoderDrive.h"
#include "commands/CmdAutoIntake.h"
#include "commands/CmdIntakeStop.h"

#include <iostream>

CmdAutoRoutineOne::CmdAutoRoutineOne() : CommandGroup("CmdAutoRoutineOne: Vanilla") {
  //AddParallel(new CmdAutoIntake());
  AddSequential(new CmdAutoEncoderDrive(autoRoutineOneLegOne)); //Init line -> end trench
  //AddSequential(new CmdAutoEncoderDrive(autoRoutineOneLegTwo));  
  //AddSequential(new CmdAutoEncoderDrive(autoRoutineOneLegThree));//End trench -> start trench
  //AddSequential(new CmdIntakeStop());
  //AddSequential(new CmdAutoEncoderDrive(autoRoutineOneLegFour)); //Start trench -> init line
  //AddSequential(new CmdAutoEncoderDrive(autoRoutineOneLegFive));
  
//init line -> target zone
}
