/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdAutoRoutineThree.h"
#include "commands/CmdAutoEncoderDrive.h"
#include "commands/CmdAutoIntake.h"
#include "commands/CmdIntakeStop.h"
#include "commands/CmdDeployIntake.h"
#include "commands/CmdStorageExpand.h"
#include "commands/CmdStorageRetract.h"
#include "commands/CmdAutoStorage.h"
#include "commands/CmdAutoStorageStop.h"
#include "commands/CmdShooterShoot.h"
#include "commands/CmdAutowait.h"

CmdAutoRoutineThree::CmdAutoRoutineThree() {
  // Add Commands here:
  // e.g. AddSequential(new Command1());
  //      AddSequential(new Command2());
  // these will run in order.

  // To run multiple commands at the same time,
  // use AddParallel()
  // e.g. AddParallel(new Command1());
  //      AddSequential(new Command2());
  // Command1 and Command2 will run in parallel.

  // A command group will require all of the subsystems that each member
  // would require.
  // e.g. if Command1 requires chassis, and Command2 requires arm,
  // a CommandGroup containing them would require both the chassis and the
  // arm.
  AddParallel(new CmdDeployIntake());
  AddParallel(new CmdAutoIntake());
  AddParallel(new CmdStorageExpand(), 0.5);
  AddParallel(new CmdAutoStorage());
  AddSequential(new CmdAutoEncoderDrive(autoRoutineThreeLegOne)); 
  AddSequential(new CmdAutoEncoderDrive(autoRoutineThreeLegTwo));  
  AddSequential(new CmdIntakeStop());
  AddParallel(new CmdStorageRetract(), 1);
  AddParallel(new CmdAutoStorageStop());
  AddSequential(new CmdAutoEncoderDrive(autoRoutineThreeLegThree));

  AddParallel(new CmdShooterShoot(), 4);
  AddSequential(new CmdAutowait(1));
  AddParallel(new CmdAutoStorage());
  AddSequential(new CmdAutowait(3));
  AddParallel(new CmdAutoStorageStop());
}
