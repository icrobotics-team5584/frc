#include "CmdAuto_Middle_Switch_Left.h"
#include "Commands/CmdOutput.h"
#include "Commands/AutonomousCommands/CmdAuto_MotionProfile.h"
#include "Commands/CmdArmPosSwitch.h"
#include "CmdAuto_BasicDrive.h"
#include "Commands/CmdArmPosGround.h"

CmdAuto_Middle_Switch_Left::CmdAuto_Middle_Switch_Left() {
	/*
	 * Start next to the exchange and place a cube in the left side of the switch
	 */

	AddParallel(new CmdArmPosSwitch());									//Deploy arm with cube
	AddSequential(new CmdAuto_MotionProfile("Middle-Switch-Left", 5));	//Drive to switch
	AddSequential(new CmdOutput(1, 1));									//Output cube
	AddSequential(new CmdAuto_BasicDrive(-0.4, 0, 5));					//Drive Backward
	AddSequential(new CmdArmPosGround());								//Arm to ground
}
