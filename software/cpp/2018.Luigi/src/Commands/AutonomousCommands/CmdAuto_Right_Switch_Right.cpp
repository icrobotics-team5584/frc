#include "CmdAuto_Right_Switch_Right.h"
#include "CmdAuto_MotionProfile.h"
#include "Commands/CmdOutput.h"
#include "Commands/AutonomousCommands/CmdAuto_DeployArm.h"
#include "Commands/CmdArmPosSwitch.h"

CmdAuto_Right_Switch_Right::CmdAuto_Right_Switch_Right() {

	/*
	 * Drive from the right start position and place a cube in the right side of the switch
	 */

	AddParallel(new CmdArmPosSwitch());
	AddSequential(new CmdAuto_MotionProfile("Right-Switch-Right", 7));
	AddSequential(new CmdOutput(1, 1));

}
