#include "CmdAuto_Right_Scale_Left.h"
#include "Commands/CmdGyroDrive.h"
#include "CmdAuto_BasicDrive.h"
#include "Commands/CmdArmPosScale.h"
#include "Commands/CmdArmPosExchange.h"
#include "Commands/CmdOutput.h"

CmdAuto_Right_Scale_Left::CmdAuto_Right_Scale_Left() {
	/*
	 * Start on the right, drive around the switch, put a cube
	 * in the scale.
	 */

	//GyroDive(distance, angle, isQuickTurn = false, relative = false)

	AddParallel(new CmdArmPosExchange());				//Deploy arm
	AddSequential(new CmdGyroDrive(5.3, 0), 5);			//Drive to gap between switch and scale
	AddSequential(new CmdGyroDrive(0, -90, true), 2);	//Turn toward gap
	AddSequential(new CmdGyroDrive(4.1, -90), 5);		//Drive over cable to opposite side of switch
	AddSequential(new CmdGyroDrive(0, 0, true), 2);		//Turn toward Scale
	AddParallel(new CmdArmPosScale());					//Lift arm to scale height
	AddSequential(new CmdAuto_BasicDrive(0.3, 0, 3));	//Drive slowly into scale
	AddSequential(new CmdOutput(1,1));					//Output cube
	AddSequential(new CmdAuto_BasicDrive(0.3, 0, 3));	//Drive slowly backward a safe distance
	AddSequential(new CmdArmPosExchange());				//Drop arm to exchange position
}
