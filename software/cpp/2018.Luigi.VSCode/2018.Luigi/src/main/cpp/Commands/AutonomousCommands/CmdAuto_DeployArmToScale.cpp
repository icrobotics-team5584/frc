#include "CmdAuto_DeployArmToScale.h"
#include "Commands/CmdArmPosScale.h"
#include "Commands/CmdArmPosSwitch.h"
#include "CmdAuto_Wait.h"
#include "Commands/CmdIntake.h"
#include "Commands/CmdIntakeAuto.h"

CmdAuto_DeployArmToScale::CmdAuto_DeployArmToScale(double offsetTime) {

	/*
	 * Deploy arm to switch position for driving, then after a number of
	 * seconds equal to offsetTime, move the arm to the scale position.
	 */

	AddParallel(new CmdArmPosSwitch());									//Deploy arm with cube
	AddParallel(new CmdIntakeAuto(2, 1));
	AddSequential(new CmdAuto_Wait(offsetTime));
	AddSequential(new CmdArmPosScale());

}
