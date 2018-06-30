/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CmdMiddleSwitchLeft.h"
#include "CmdAutoDrive.h"
#include "CmdAutoTurn.h"

CmdMiddleSwitchLeft::CmdMiddleSwitchLeft() {

	AddSequential(new CmdAutoDrive(1));
	AddSequential(new CmdAutoTurn(-45));
	AddSequential(new CmdAutoDrive(1));
	AddSequential(new CmdAutoTurn(0));
	AddSequential(new CmdAutoDrive(1));





}
