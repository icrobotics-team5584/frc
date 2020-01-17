/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdAutoRoutineOne.h"
#include "commands/CmdAutoEncoderDrive.h"
CmdAutoRoutineOne::CmdAutoRoutineOne() {
  //Update Values when robot lengths are confirmed
  AddSequential(new CmdAutoEncoderDrive(-1.7, -0.9, 0.00001, -42, -0.8, 4.537));
  AddSequential(new CmdAutoEncoderDrive(-1.7, 0.9, -0.00001, 42, 0.8, 2.312));
  AddSequential(new CmdAutoEncoderDrive(0, 0.9, -0.00001, 42, 0.8, 0));
  AddSequential(new CmdAutoEncoderDrive(0, 3, -0.0, 80, 0.5, -2.553));

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
