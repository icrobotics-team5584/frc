#include "CmdAuto_Left_Scale_Left.h"
#include "Commands/CmdOutput.h"
#include "CmdAuto_MotionProfile.h"
#include "Commands/CmdArmPosScale.h"
#include "CmdAuto_BasicDrive.h"
#include "Commands/CmdArmPosGround.h"

CmdAuto_Left_Scale_Left::CmdAuto_Left_Scale_Left() {
	/*
	 * From the left starting position, put a cube in the left side of the scale
	 */

	AddParallel(new CmdArmPosScale());									//Lift arm to scale height
	AddSequential(new CmdAuto_MotionProfile("Left-Scale-Left", 10));	//Drive to scale
	AddSequential(new CmdOutput(1, 1));									//Output cube
	AddSequential(new CmdAuto_BasicDrive(-0.6, 0, 0.7));				//Drive back a safe distance
}
