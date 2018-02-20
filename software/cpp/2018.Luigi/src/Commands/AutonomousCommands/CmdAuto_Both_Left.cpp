#include "CmdAuto_Both_Left.h"
#include "CmdAuto_Left_Scale_Left.h"
#include "CmdAuto_BasicDrive.h"
#include "Commands/CmdGyroDrive.h"
#include "Commands/CmdIntake.h"
#include "Commands/CmdArmPosSwitch.h"
#include "Commands/CmdOutput.h"

CmdAuto_Both_Left::CmdAuto_Both_Left() {
	/*
	 * Start on the left, get a cube in the left scale and
	 * then a second cube in the left switch.
	 */

	AddSequential(new CmdAuto_Left_Scale_Left());	//Get a cube in the scale
	AddParallel(new CmdIntake(5, 1));				//Run intake
	AddSequential(new CmdGyroDrive(1, 180));		//Drive toward a cube
	AddSequential(new CmdArmPosSwitch());			//Lift arm to switch height
	AddSequential(new CmdOutput(1,1));				//Output the cube
}
