/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdSeekRocketSide.h"
#include "commands/CmdSeekRocketCargo.h"
#include "commands/CmdStopAtLine.h"
#include "commands/CmdEncoderDrive.h"
#include "subsystems/SubDriveBase.h"
CmdSeekRocketSide::CmdSeekRocketSide() {
  // Add Commands here:
  // e.g. AddSequential(new Command1());
  //      AddSequential(new Command2());
  AddSequential(new CmdStopAtLine(0.8));
  AddSequential(new CmdEncoderDrive(-0.235)); //Dizzy was 0.235, change pid output to neg for dizzy
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
