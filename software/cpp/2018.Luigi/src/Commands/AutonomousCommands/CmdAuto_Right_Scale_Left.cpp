#include "CmdAuto_Right_Scale_Left.h"
#include "Commands/CmdGyroDrive.h"
#include "CmdAuto_BasicDrive.h"
#include "Commands/CmdArmPosScale.h"
#include "Commands/CmdArmPosExchange.h"
#include "Commands/CmdArmPosSwitch.h"
#include "Commands/CmdArmPosScaleAuto.h"
#include "Commands/CmdOutput.h"

CmdAuto_Right_Scale_Left::CmdAuto_Right_Scale_Left() {
	/*
	 * Start on the right, drive around the switch, put a cube
	 * in the scale.
	 */

	//GyroDive(distance, angle, isQuickTurn = false, relative = false)

	AddParallel(new CmdArmPosSwitch());							//Deploy arm
	AddSequential(new CmdGyroDrive(5.5, 0), 3);					//Drive to gap between switch and scale
	AddSequential(new CmdGyroDrive(0, -90, true), 2);			//Turn toward gap
	AddSequential(new CmdGyroDrive(5.8, -90, false, true), 5);	//Drive slowly over cable to opposite side of switch
	AddParallel(new CmdArmPosScaleAuto());						//Lift arm to scale height
	AddSequential(new CmdGyroDrive(0, 20, true), 2);			//Turn slowly toward Scale
	AddSequential(new CmdGyroDrive(1.2, 20, false, true), 2);	//Drive slowly into scale
	AddSequential(new CmdOutput(1,1));							//Output cube
	AddSequential(new CmdGyroDrive(-0.5, 0, false, true), 2);	//Drive slowly backward
	AddSequential(new CmdArmPosExchange());						//Drop arm to exchange position
}
