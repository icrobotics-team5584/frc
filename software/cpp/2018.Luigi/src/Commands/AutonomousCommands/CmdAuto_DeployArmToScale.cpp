#include "CmdAuto_DeployArmToScale.h"
#include "Commands/CmdArmPosScale.h"
#include "CmdAuto_DeployArm.h"
#include "CmdAuto_Wait.h"

CmdAuto_DeployArmToScale::CmdAuto_DeployArmToScale(double offsetTime) {
	AddParallel(new CmdAuto_DeployArm());
	AddSequential(new CmdAuto_Wait(offsetTime));
	AddSequential(new CmdArmPosScale());
}
