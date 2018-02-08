#include "CmdAuto_Left_Scale_Left.h"
#include "CmdAuto_DeployArm.h"
#include "Commands/CmdOutput.h"
#include "Commands/CmdArmPosScale.h"
#include "CmdAuto_MotionProfile.h"
#include "CmdAuto_Wait.h"

CmdAuto_Left_Scale_Left::CmdAuto_Left_Scale_Left() {
	/*
	 * From the left starting position, put a cube in the left side of the scale
	 */


	AddParallel(new CmdAuto_DelayedLift());
	AddSequential(new CmdAuto_MotionProfile("Left-Scale-Left", 10));
	AddSequential(new CmdOutput(1, 1));
}

CmdAuto_Left_Scale_Left::CmdAuto_DelayedLift::CmdAuto_DelayedLift(){
	std::cout << "Beginning delayed lift" << std::endl;
	AddParallel(new CmdAuto_DeployArm());
	AddSequential(new CmdAuto_Wait(5.5));
	AddSequential(new CmdArmPosScale());
}
