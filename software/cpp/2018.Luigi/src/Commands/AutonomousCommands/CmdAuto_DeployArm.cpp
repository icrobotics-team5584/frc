#include <Commands/AutonomousCommands/CmdAuto_DeployArm.h>
#include "Commands/CmdArmPosSwitch.h"
#include "Commands/CmdIntake.h"
#include "Commands/CmdOutput.h"

CmdAuto_DeployArm::CmdAuto_DeployArm() {
	/*
	 * Run intake quickly while arm deploys, then intake it slowly for the rest of the run
	 */

	AddParallel(new CmdArmPosSwitch());			//Deoply arm
	AddSequential(new CmdIntake(2, 1));			//fast intake to avoid dropping cube on lift deployment
	AddSequential(new CmdIntake(13, 0.75));		//Slow intake to avoid dropping cube on fast turn
}
