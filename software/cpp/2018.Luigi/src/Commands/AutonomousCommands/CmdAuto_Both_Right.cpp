#include "CmdAuto_Both_Right.h"
#include "CmdAuto_Right_Scale_Right.h"
#include "CmdAuto_BasicDrive.h"
#include "Commands/CmdGyroDrive.h"
#include "Commands/CmdArmPosGround.h"
#include "Commands/CmdArmPosSwitch.h"
#include "Commands/CmdIntake.h"
#include "Commands/CmdOutput.h"

CmdAuto_Both_Right::CmdAuto_Both_Right() {
	/*
	 * Start on the right, get a cube in the right scale and
	 * then a second cube in the right switch.
	 */

	AddSequential(new CmdAuto_Right_Scale_Right());	//Get a cube in the scale
	AddSequential(new CmdGyroDrive(-1, 90));		//Drive back and turn toward the gap between switch and scale
	AddParallel(new CmdIntake(5, 1));				//Run intake
	AddSequential(new CmdGyroDrive(1, 180));		//Drive toward a cube
	AddSequential(new CmdArmPosSwitch());			//Lift arm to switch height
	AddSequential(new CmdOutput(1,1));				//Output the cube
}
