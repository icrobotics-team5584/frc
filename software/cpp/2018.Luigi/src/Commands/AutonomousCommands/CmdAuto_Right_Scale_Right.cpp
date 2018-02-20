#include "CmdAuto_Right_Scale_Right.h"
#include "Commands/CmdOutput.h"
#include "CmdAuto_MotionProfile.h"
#include "Commands/CmdArmPosScale.h"
#include "Commands/CmdArmPosGround.h"
#include "CmdAuto_BasicDrive.h"

CmdAuto_Right_Scale_Right::CmdAuto_Right_Scale_Right() {
	/*
	 * From the right starting position, put a cube in the right side of the scale
	 */

	AddParallel(new CmdArmPosScale());									//Lift arm to scale height
	AddSequential(new CmdAuto_MotionProfile("Right-Scale-Right", 10));	//Drive to scale
	AddSequential(new CmdOutput(1, 1));									//Output cube
	AddSequential(new CmdAuto_BasicDrive(-0.6, 0, 0.7));				//Drive back a safe distance
	AddSequential(new CmdArmPosGround());								//Drop the arm to ground height
}
