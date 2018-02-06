#include "CmdAuto_Left_Switch_Left.h"
#include "CmdAuto_MotionProfile.h"
#include "Commands/CmdArmPosSwitch.h"
#include "Commands/CmdIntake.h"
#include "Commands/CmdOutput.h"
#include "Commands/CmdAutonomous.h"

CmdAuto_Left_Switch_Left::CmdAuto_Left_Switch_Left() {

	/*
	 * Drive from the left start position and place a cube in the left side of the switch
	 */

	AddParallel(new CmdArmPosSwitch());								//Lift up arm
	AddParallel(new CmdAuto_IntakeSave());							//Dont drop the cube
	AddSequential(new CmdAuto_MotionProfile("Left-Switch-Left"));	//Drive to switch
	AddSequential(new CmdOutput(1, 1));								//Output cube
}

CmdAuto_Left_Switch_Left::CmdAuto_IntakeSave::CmdAuto_IntakeSave(){
	AddSequential(new CmdIntake(2, 1));								//fast intake to avoid dropping cube on lift deployment
	AddSequential(new CmdIntake(4, 0.75));							//Slow intake to avoid dropping cube on fast turn
}
