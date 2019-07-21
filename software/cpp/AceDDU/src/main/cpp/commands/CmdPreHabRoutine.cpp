/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdPreHabRoutine.h"
#include "commands/CmdArmToPreHab.h"
#include "commands/CmdCloseIntake.h"
#include "Robot.h"

CmdPreHabRoutine::CmdPreHabRoutine() {
  AddParallel(new CmdArmToPreHab());
  AddParallel(new CmdCloseIntake());
}
