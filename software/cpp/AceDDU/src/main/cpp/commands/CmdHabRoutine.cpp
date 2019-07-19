/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdHabRoutine.h"
#include "commands/CmdArmToHab.h"
#include "commands/CmdVacuum.h"
#include "commands/CmdArmToFloor.h"
#include "commands/CmdPause.h"
CmdHabRoutine::CmdHabRoutine() {
AddSequential(new CmdArmToHab); 
AddSequential(new CmdVacuum);
AddSequential(new CmdPause);
AddSequential(new CmdArmToFloor);

}
