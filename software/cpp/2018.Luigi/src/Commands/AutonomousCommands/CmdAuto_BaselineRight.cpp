#include "CmdAuto_BaselineRight.h"
#include "Commands/CmdGyroDrive.h"
#include "Commands/CmdArmPosSwitch.h"

CmdAuto_BaselineRight::CmdAuto_BaselineRight() {
	AddParallel(new CmdArmPosSwitch());
	AddSequential(new CmdGyroDrive(5.5, 0), 3);
	AddSequential(new CmdGyroDrive(0, 90, true), 2);
	AddSequential(new CmdGyroDrive(4, 90));
}
