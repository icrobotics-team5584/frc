#include "CmdAuto_Left_Switch_Left.h"
#include "CmdAuto_MotionProfile.h"
#include "Commands/CmdArmPosSwitch.h"
#include "Commands/CmdIntake.h"
#include "Commands/CmdOutput.h"
#include "Commands/CmdAutonomous.h"

CmdAuto_Left_Switch_Left::CmdAuto_Left_Switch_Left() {

	std::cout << "Running Group command: CmdAuto_Left_Switch_Left()" <<std::endl;

	AddParallel(new CmdArmPosSwitch());								//Lift up arm
	AddParallel(new CmdAuto_MotionProfile("Left-Switch-Left"));		//Drive to switch
	AddSequential(new CmdIntake(3));								//Output cube
	AddSequential(new CmdOutput());
}
