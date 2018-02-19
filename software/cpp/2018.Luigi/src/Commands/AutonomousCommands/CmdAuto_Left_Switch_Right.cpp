#include "CmdAuto_Left_Switch_Right.h"
#include "Commands/CmdGyroDrive.h"
#include "Commands/CmdArmPosExchange.h"
#include "Commands/CmdArmPosSwitch.h"
#include "Commands/CmdOutput.h"

CmdAuto_Left_Switch_Right::CmdAuto_Left_Switch_Right() {
	/*
	 * Start on the left, drive around to the other side of the
	 * switch and put a cube in it.
	 */

	//GyroDive(distance, angle, isQuickTurn = false, relative = false)

	AddParallel(new CmdArmPosExchange());				//Deploy arm
	AddSequential(new CmdGyroDrive(5.3, 0));			//Drive to gap between switch and scale
	AddSequential(new CmdGyroDrive(0, 90, true), 2);	//Turn toward gap
	AddSequential(new CmdGyroDrive(4.1, 90));			//Drive over cable to opposite side of switch
	AddSequential(new CmdGyroDrive(0, 135, true), 2);	//Turn toward switch
	AddParallel(new CmdArmPosSwitch());					//Lift arm to switch height
	AddSequential(new CmdGyroDrive(0.2, 0));			//Drive into switch
	AddSequential(new CmdOutput(1, 1));					//Output cube
	AddSequential(new CmdGyroDrive(-1, -135));			//Drive backward a safe distance
	AddSequential(new CmdArmPosExchange());				//Drop arm to exchange position
}
