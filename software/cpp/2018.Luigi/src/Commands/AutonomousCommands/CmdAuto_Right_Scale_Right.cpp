#include "CmdAuto_Right_Scale_Right.h"
#include "Commands/CmdOutput.h"
#include "CmdAuto_MotionProfile.h"
#include "CmdAuto_DeployArmToScale.h"
#include "CmdAuto_BasicDrive.h"

CmdAuto_Right_Scale_Right::CmdAuto_Right_Scale_Right() {
	/*
	 * From the right starting position, put a cube in the right side of the scale
	 */
	AddParallel(new CmdAuto_DeployArmToScale());
	AddSequential(new CmdAuto_MotionProfile("Right-Scale-Right", 10));
	AddSequential(new CmdOutput(1, 1));
	AddSequential(new CmdAuto_BasicDrive(-0.4, 0, 5));
}
