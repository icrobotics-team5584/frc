#include "CmdAuto_Both_Left.h"
#include "CmdAuto_Left_Scale_Left.h"
#include "CmdAuto_BasicDrive.h"
#include "Commands/CmdGyroDrive.h"
#include "Commands/CmdIntake.h"
#include "Commands/CmdArmPosSwitch.h"
#include "Commands/CmdArmPosGround.h"
#include "Commands/CmdArmPosScale.h"
#include "Commands/CmdOutput.h"
#include "CmdAuto_Wait.h"

CmdAuto_Both_Left::CmdAuto_Both_Left() {
	/*
	 * Start on the left, get a cube in the left scale and
	 * then a second cube in the left switch.
	 */

//	AddSequential(new CmdAuto_Left_Scale_Left());	//Get a cube in the scale
	AddParallel(new CmdArmPosSwitch());							//Deploy arm to switch
	AddSequential(new CmdGyroDrive(5.5, 0), 3.2);					//Deploy arm to switch
	AddParallel(new CmdArmPosScale());							//Raise arm to scale height
	AddSequential(new CmdGyroDrive(0, 55, true, true), 1);		//Turn toward scale
	AddSequential(new CmdGyroDrive(1.3, 45, false, true), 1.7);	//Slowly drive into scale
	AddSequential(new CmdOutput(1,0.5), 0.5);						//Output the cube
	AddParallel(new CmdArmPosGround());							//Drop arm to ground position
	AddSequential(new CmdGyroDrive(-0.5, 45, false, true), 1);	//Drive back a safe distance
	AddSequential(new CmdAuto_Wait(1));							//Wait for arm to be lower
	AddSequential(new CmdGyroDrive(0,160,true), 1.2);			//Turn toward switch
	AddParallel(new CmdIntake(4, 1));							//Run intake
	AddSequential(new CmdGyroDrive(1.6, 160), 2.5);				//Drive toward a cube
	AddSequential(new CmdArmPosSwitch(), 1);					//Lift arm to switch height
	AddSequential(new CmdOutput(1,1));							//Output the cube
}
