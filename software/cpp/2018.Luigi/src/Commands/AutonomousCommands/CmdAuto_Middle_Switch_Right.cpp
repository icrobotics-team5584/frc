#include "CmdAuto_Middle_Switch_Right.h"
#include "Commands/CmdOutput.h"
#include "Commands/AutonomousCommands/CmdAuto_MotionProfile.h"
#include "Commands/AutonomousCommands/CmdAuto_DeployArm.h"

CmdAuto_Middle_Switch_Right::CmdAuto_Middle_Switch_Right() {
	/*
	 * Start next to the exchange and place a cube in the right side of the switch
	 */

	AddParallel(new CmdAuto_DeployArm());								//Deploy arm with cube
	AddSequential(new CmdAuto_MotionProfile("Middle-Switch-Right", 4));	//Drive to switch
	AddSequential(new CmdOutput(1, 1));									//Output cube
}
