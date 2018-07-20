/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CmdMiddleSwitchLeft.h"
#include "CmdAutoDrive.h"
#include "CmdAutoTurn.h"
#include "CmdSpit.h"
#include "CmdArmBackMid.h"
#include "CmdArmFront.h"

CmdMiddleSwitchLeft::CmdMiddleSwitchLeft() {

	AddParallel(new CmdArmBackMid());			//Move arm
	AddSequential(new CmdAutoDrive(0.5, 0));	//Drive
	AddSequential(new CmdAutoTurn(-45), 2);		//Turn left
	AddSequential(new CmdAutoDrive(2, -45));	//Drive
	AddSequential(new CmdAutoTurn(0),1.5);		//Turn right
	AddSequential(new CmdAutoDrive(1, 0),2);	//Drive
	AddSequential(new CmdSpit(true),0.5);		//Ouptut cube
	AddSequential(new CmdArmFront());





}
