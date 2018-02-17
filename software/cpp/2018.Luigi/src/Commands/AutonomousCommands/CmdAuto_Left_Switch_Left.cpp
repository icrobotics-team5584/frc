#include "CmdAuto_Left_Switch_Left.h"
#include "CmdAuto_MotionProfile.h"
#include "Commands/CmdOutput.h"
#include "Commands/AutonomousCommands/CmdAuto_DeployArm.h"

CmdAuto_Left_Switch_Left::CmdAuto_Left_Switch_Left() {

	/*
	 * Drive from the left start position and place a cube in the left side of the switch
	 */

	AddParallel(new CmdAuto_DeployArm());							//Deploy arm
	AddSequential(new CmdAuto_MotionProfile("Left-Switch-Left", 7));//Drive to switch
	AddSequential(new CmdOutput(1, 1));								//Output cube

	// sample code to demo the multiple motion profiles in sequence ...
	// AddSequential(new CmdAuto_MotionProfile("Left-Baseline-Left", 7));
	// AddSequential(new CmdAuto_MotionProfile("Left-Retreat-Left", 7));
	// AddSequential(new CmdAuto_MotionProfile("Left-Baseline-Left", 7));
	// AddSequential(new CmdAuto_MotionProfile("Left-Retreat-Left", 7));

}
