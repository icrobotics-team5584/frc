#include "CmdAuto_Left_Scale_Left.h"
#include "CmdAuto_DeployArm.h"
#include "Commands/CmdOutput.h"
#include "Commands/CmdArmPosScale.h"
#include "CmdAuto_MotionProfile.h"

CmdAuto_Left_Scale_Left::CmdAuto_Left_Scale_Left() {
	/*
	 * From the left starting positoin, put a cube in the left side of the scale
	 */

	AddParallel(new CmdAuto_DeployArm());
	AddSequential(new CmdAuto_MotionProfile("Left-Scale-Left-pt1", 8));
	AddParallel(new CmdArmPosScale());
	AddSequential(new CmdAuto_MotionProfile("Left-Scale-Left-pt2", 7));
	AddSequential(new CmdOutput(1, 1));
}
