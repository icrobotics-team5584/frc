#include "CmdAuto_Left_Scale_Right.h"
#include "Commands/CmdOutput.h"
#include "CmdAuto_MotionProfile.h"
#include "CmdAuto_DeployArmToScale.h"
#include "CmdAuto_BasicDrive.h"

CmdAuto_Left_Scale_Right::CmdAuto_Left_Scale_Right() {
	/*
	 * From the left starting position, put a cube in the right side of the scale
	 */

	AddParallel(new CmdAuto_DeployArmToScale(15));
	AddSequential(new CmdAuto_MotionProfile("Left-Scale-Right", 15));
//	AddSequential(new CmdOutput(1, 1));
}
