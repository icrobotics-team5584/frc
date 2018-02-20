#include "CmdAuto_Both_Left.h"
#include "CmdAuto_Left_Scale_Left.h"
#include "CmdAuto_BasicDrive.h"
#include "Commands/CmdGyroDrive.h"
#include "Commands/CmdIntake.h"
#include "Commands/CmdArmPosSwitch.h"
#include "Commands/CmdArmPosGround.h"
#include "Commands/CmdArmPosScale.h"
#include "Commands/CmdOutput.h"

CmdAuto_Both_Left::CmdAuto_Both_Left() {
	/*
	 * Start on the left, get a cube in the left scale and
	 * then a second cube in the left switch.
	 */

//	AddSequential(new CmdAuto_Left_Scale_Left());	//Get a cube in the scale
	AddParallel(new CmdArmPosSwitch());						//Deploy arm to switch
	AddSequential(new CmdGyroDrive(5.5, 0), 5);				//Deploy arm to switch
	AddParallel(new CmdArmPosScale());						//Raise arm to scale height
	AddSequential(new CmdGyroDrive(0, 55, true, true), 3);		//Turn toward scale
	AddSequential(new CmdGyroDrive(1.3, 45, false, true), 5);	//Slowly drive into scale
	AddSequential(new CmdOutput(1,1));					//Output the cube
	AddSequential(new CmdGyroDrive(-0.7, 45, false, true), 3);	//Drive back a safe distance
	AddSequential(new CmdArmPosGround());					//Drop arm to ground position
	AddSequential(new CmdGyroDrive(0,165,true), 3);			//Turn toward switch
	AddParallel(new CmdIntake(5, 1));						//Run intake
	AddSequential(new CmdGyroDrive(1.6, 165), 5);				//Drive toward a cube
	AddSequential(new CmdArmPosSwitch());					//Lift arm to switch height
	AddSequential(new CmdAuto_BasicDrive(0.5, 0, 1));		//Drive into switch
	AddSequential(new CmdOutput(1,1));					//Output the cube
}
