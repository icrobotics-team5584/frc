#include "CmdAuto_Right_Switch_Right.h"
#include "CmdAuto_MotionProfile.h"
#include "Commands/CmdOutput.h"
#include "Commands/CmdArmPosSwitch.h"
#include "CmdAuto_BasicDrive.h"
#include "Commands/CmdArmPosExchange.h"

CmdAuto_Right_Switch_Right::CmdAuto_Right_Switch_Right() {

	/*
	 * Drive from the right start position and place a cube in the right side of the switch
	 */

	AddParallel(new CmdArmPosSwitch());									//Deploy arm with cube
	AddSequential(new CmdAuto_MotionProfile("Right-Switch-Right", 7));
	AddSequential(new CmdOutput(1, 0.5));
	AddSequential(new CmdAuto_BasicDrive(-0.4, 0, 5));					//Drive backwards
	AddSequential(new CmdArmPosExchange());								//Drop the arm for teleop
}
