#include "CmdAuto_Left_Switch_Right.h"
#include "Commands/CmdGyroDrive.h"
#include "Commands/CmdArmPosScale.h"
#include "CmdAuto_DeployArm.h"
#include "Commands/CmdOutput.h"

CmdAuto_Left_Switch_Right::CmdAuto_Left_Switch_Right() {
	AddParallel(new CmdAuto_DeployArm());			//Deploy arm to switch position
	AddSequential(new CmdGyroDrive(4, 0));			//Drive forward
	AddSequential(new CmdGyroDrive(0.5, 90), 2);	//Turn right
	AddSequential(new CmdGyroDrive(4, 0));			//Drive forward
	AddSequential(new CmdGyroDrive(0.5, -90), 2);	//Turn left
	AddParallel(new CmdArmPosScale());				//Raise arm to switch position
	AddSequential(new CmdGyroDrive(2, 0));			//Drive forward
	AddSequential(new CmdOutput(1, 1));				//Output cube
}
