#include "CmdAuto_Left_Switch_Left.h"

CmdAuto_Left_Switch_Left::CmdAuto_Left_Switch_Left() {

	std::cout << "Running CmdAuto_Left_Switch_Left()" <<std::endl;

	AddParallel(new CmdArmPosSwitch());								//Lift up arm
	AddParallel(new CmdAuto_MotionProfile("Left-Switch-Left"));		//Drive to switch
	AddSequential(new CmdOutput());									//Output cube

}
