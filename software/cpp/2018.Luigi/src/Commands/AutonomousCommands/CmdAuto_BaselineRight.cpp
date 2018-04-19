#include "CmdAuto_BaselineRight.h"
#include "Commands/CmdGyroDrive.h"
#include "Commands/CmdArmPosSwitch.h"
#include "Commands/CmdIntakeAuto.h"

CmdAuto_BaselineRight::CmdAuto_BaselineRight() {
	AddParallel(new CmdArmPosSwitch());
	AddParallel(new CmdIntakeAuto(2, 1));		//Houston task 6: Run the intake motors
	AddSequential(new CmdGyroDrive(5.5, 0), 3);
	AddSequential(new CmdGyroDrive(0, 90, true), 2);
	AddSequential(new CmdGyroDrive(1, 90), 2);	//Houston task 4: End on a 1m straight drive
}
