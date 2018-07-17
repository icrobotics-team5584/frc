/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CmdRightSwitchRight.h"
#include "CmdAutoDrive.h"
#include "CmdAutoTurn.h"
#include "CmdArmBackMid.h"
#include "CmdArmFront.h"
#include "CmdSpit.h"

CmdRightSwitchRight::CmdRightSwitchRight() {

	AddParallel(new CmdArmBackMid());
	AddSequential(new CmdAutoDrive(4, 0));
	AddSequential(new CmdAutoTurn(-90));
	AddSequential(new CmdAutoDrive(0.5, -90));
	AddSequential(new CmdSpit(), 1);
	AddSequential(new CmdArmFront());
}
