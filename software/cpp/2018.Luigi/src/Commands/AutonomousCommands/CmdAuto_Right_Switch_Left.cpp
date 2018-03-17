#include "CmdAuto_Right_Switch_Left.h"
#include "Commands/CmdArmPosExchange.h"
#include "Commands/CmdArmPosSwitch.h"
#include "Commands/CmdGyroDrive.h"
#include "Commands/CmdOutput.h"
#include "Commands/CmdIntakeAuto.h"

CmdAuto_Right_Switch_Left::CmdAuto_Right_Switch_Left() {
	/*
	 * Start on the right, drive around to the other side of the
	 * switch and put a cube in it.
	 */

	//GyroDive(distance, angle, isQuickTurn = false, relative = false)

	AddParallel(new CmdArmPosSwitch());							//Deploy arm
	AddParallel(new CmdIntakeAuto(2, 1));
	AddSequential(new CmdGyroDrive(5.5, 0), 3);					//Drive to gap between switch and scale
	AddSequential(new CmdGyroDrive(0, -90, true), 2);			//Turn toward gap
	AddSequential(new CmdGyroDrive(5.8, -90, false, true), 9);	//Drive over cable to opposite side of switch
	AddSequential(new CmdGyroDrive(0, -135, true), 3);			//Turn toward switch
	AddSequential(new CmdGyroDrive(0.5, -135), 3);				//Drive into switch
	AddSequential(new CmdOutput(1,1));							//Output cube
	AddSequential(new CmdGyroDrive(-1, -135));					//Drive backward a safe distance
	AddSequential(new CmdArmPosExchange());						//Drop arm to exchange position
}
