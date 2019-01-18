#include "CmdAuto_Middle_Switch_Left.h"
#include "Commands/CmdOutput.h"
#include "Commands/AutonomousCommands/CmdAuto_MotionProfile.h"
#include "Commands/CmdArmPosSwitch.h"
#include "CmdAuto_BasicDrive.h"
#include "Commands/CmdArmPosGround.h"
#include "Commands/CmdIntakeAuto.h"

CmdAuto_Middle_Switch_Left::CmdAuto_Middle_Switch_Left() {
	/*
	 * Start next to the exchange and place a cube in the left side of the switch
	 */

	AddParallel(new CmdArmPosSwitch());									//Deploy arm with cube
	AddParallel(new CmdIntakeAuto(2, 1));
	AddSequential(new CmdAuto_MotionProfile("Middle-Switch-Left", 5));	//Drive to switch
	AddSequential(new CmdOutput(1, 0.5));								//Output cube
}
