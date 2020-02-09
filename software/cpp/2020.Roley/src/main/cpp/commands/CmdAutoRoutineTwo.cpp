/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdAutoRoutineTwo.h"
#include "commands/CmdAutoEncoderDrive.h"
#include "commands/CmdAutoIntake.h"
#include "commands/CmdIntakeStop.h"


#include <iostream>
CmdAutoRoutineTwo::CmdAutoRoutineTwo() : CommandGroup("CmdAutoRoutineTwo: Steal") {
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
 // AddParallel(new CmdAutoIntake());
 AddSequential(new CmdAutoEncoderDrive(autoRoutineTwoLegOne));
 // AddSequential(new CmdIntakeStop());
}

void CmdAutoRoutineTwo::Initialize(){
  std::cout << "routine init" << std::endl;
}

void CmdAutoRoutineTwo::Execute(){
  std::cout << "routine exe" << std::endl;
}
