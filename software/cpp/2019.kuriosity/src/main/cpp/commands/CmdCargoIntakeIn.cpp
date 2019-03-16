/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdCargoIntakeIn.h"
#include "commands/CmdElevatortoIntakeHeight.h"
#include "commands/CmdIntakeOutakeIn.h"
#include "commands/CmdElevatorToBottom.h"
#include "commands/CmdMoveRollerIntakeBar.h"
#include "commands/CmdIntakeOutakeStop.h"
#include "commands/CmdGimblePidCentre.h"
#include "subsystems/SubRollerIntakeBar.h"

CmdCargoIntakeIn::CmdCargoIntakeIn() {
  AddParallel(new CmdIntakeOutakeStop());
  AddParallel(new CmdGimblePidCentre());
  AddSequential(new CmdElevatortoIntakeHeight());
  AddSequential(new CmdMoveRollerIntakeBar(IN));
  // AddSequential(new CmdElevatorToBottom());
}
