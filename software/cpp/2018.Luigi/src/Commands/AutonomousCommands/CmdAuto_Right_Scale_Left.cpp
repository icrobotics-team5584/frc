#include "CmdAuto_Right_Scale_Left.h"
#include "Commands/CmdArmPosExchange.h"
#include "Commands/CmdGyroDrive.h"

CmdAuto_Right_Scale_Left::CmdAuto_Right_Scale_Left() {
	AddParallel(new CmdArmPosExchange());
	AddSequential(new CmdGyroDrive(6,0,false,false), 5);
	AddSequential(new CmdGyroDrive(0,-90,false,true), 2);
	AddSequential(new CmdGyroDrive(4, 0, true, false), 5);
	AddSequential(new CmdGyroDrive(0, 0, false, true), 2);
}
