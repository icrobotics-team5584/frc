#include "CmdAuto_Left_Switch_Left.h"
#include "CmdAuto_MotionProfile.h"
#include "Commands/CmdOutput.h"
#include "Commands/CmdArmPosSwitch.h"
#include "CmdAuto_BasicDrive.h"
#include "Commands/CmdArmPosExchange.h"

CmdAuto_Left_Switch_Left::CmdAuto_Left_Switch_Left() {

	/*
	 * Drive from the left start position and place a cube in the left side of the switch
	 */

	AddParallel(new CmdArmPosSwitch());									//Deploy arm with cube
	AddSequential(new CmdAuto_MotionProfile("Left-Switch-Left", 5));	//Drive to switch
	AddSequential(new CmdOutput(1, 0.5));								//Output cube
	AddSequential(new CmdAuto_BasicDrive(-0.4, 0, 5));					//Drive backwards
	AddSequential(new CmdArmPosExchange());								//Drop the arm for teleop
}
