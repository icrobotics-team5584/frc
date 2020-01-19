/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdAutoRoutineOne.h"
#include "commands/CmdAutoEncoderDrive.h"


#include <iostream>

CmdAutoRoutineOne::CmdAutoRoutineOne() {
  AddSequential(new CmdAutoEncoderDrive(autoRoutineOneLegOne)); //Init line -> end trench
  AddSequential(new CmdAutoEncoderDrive(autoRoutineOneLegTwo)); //End trench -> start trench
  AddSequential(new CmdAutoEncoderDrive(autoRoutineOneLegThree));//Start trench -> init line
  AddSequential(new CmdAutoEncoderDrive(autoRoutineOneLegFour));//init line -> target zone
}
