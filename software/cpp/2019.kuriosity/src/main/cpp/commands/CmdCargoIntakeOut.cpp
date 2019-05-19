/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdCargoIntakeOut.h"
#include "commands/CmdElevatortoIntakeHeight.h"
#include "commands/CmdGimblePidCentre.h"
#include "commands/CmdIntakeOutakeIn.h"
#include "commands/CmdElevatorToBottom.h"
#include "commands/CmdMoveRollerIntakeBar.h"
#include "subsystems/SubRollerIntakeBar.h"

CmdCargoIntakeOut::CmdCargoIntakeOut() {

  AddParallel(new CmdGimblePidCentre());
  AddSequential(new CmdElevatortoIntakeHeight());
  AddSequential(new CmdMoveRollerIntakeBar(OUT));
  AddParallel(new CmdElevatorToBottom());
  //AddSequential(new CmdIntakeOutakeIn());
  
}
