/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdAutoRoutineOne.h"
#include "commands/CmdAutoEncoderDrive.h"
#include "commands/CmdIntake.h"
#include "commands/CmdIntakeStop.h"
#include "commands/CmdAutoIntakeDeploy.h"
#include "commands/CmdAutoShoot.h"
#include "commands/CmdAutoStorage.h"
#include <iostream>

CmdAutoRoutineOne::CmdAutoRoutineOne() : CommandGroup("CmdAutoRoutineOne: Vanilla") {
  //AddParallel(new CmdAutoIntake());
  AddParallel(new CmdAutoIntakeDeploy());
  AddParallel(new CmdAutoShoot(), 3);
  AddSequential(new CmdAutoEncoderDrive(autoRoutineOneLegOne));
  AddSequential(new CmdAutoStorage(), 1);
  AddSequential(new CmdAutoEncoderDrive(autoRoutineOneLegTwo));
  AddParallel(new CmdIntake(), 4); 
  AddSequential(new CmdAutoEncoderDrive(autoRoutineOneLegThree));
  AddSequential(new CmdAutoEncoderDrive(autoRoutineOneLegFour)); 
  AddSequential(new CmdAutoEncoderDrive(autoRoutineOneLegFive));
  AddParallel(new CmdAutoShoot(), 3);
  AddSequential(new CmdAutoEncoderDrive(autoRoutineOneLegSix));
  AddSequential(new CmdAutoStorage(), 1);


  
//init line -> target zone
}
