/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdShooterSquence.h"
#include "commands/CmdStartShoot.h"
#include "commands/CmdStopShoot.h"
#include "commands/CmdStorageRetract.h"
#include "commands/CmdRollStorage.h"
#include "commands/CmdDeployIntake.h"
#include "commands/CmdDeployIntakeOnly.h"
#include "Robot.h"
#include "commands/CmdShooterShoot.h"


CmdShooterSquence::CmdShooterSquence() {
  AddSequential(new CmdStorageRetract(), 0.5);
  AddParallel(new CmdStartShoot(), 0.1);
  AddParallel(new CmdDeployIntakeOnly());
  AddParallel(new CmdStopShoot());
  AddSequential(new CmdRollStorage());

  




  

  

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
}
