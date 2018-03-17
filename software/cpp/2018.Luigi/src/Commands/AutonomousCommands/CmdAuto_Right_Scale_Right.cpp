#include "CmdAuto_Right_Scale_Right.h"
#include "Commands/CmdOutput.h"
#include "CmdAuto_MotionProfile.h"
#include "Commands/CmdArmPosScale.h"
#include "CmdAuto_BasicDrive.h"
#include "Commands/CmdArmPosExchange.h"
#include "Commands/CmdArmPosSwitch.h"
#include "Commands/CmdGyroDrive.h"
#include "Commands/CmdArmPosGround.h"
#include "Commands/CmdIntakeAuto.h"

CmdAuto_Right_Scale_Right::CmdAuto_Right_Scale_Right() {

	/*
	 * From the right starting position, put a cube in the right side of the scale
	 */

//	AddParallel(new CmdArmPosScale());									//Lift arm to scale height
//	AddSequential(new CmdAuto_MotionProfile("Right-Scale-Right", 10));	//Drive to scale
//	AddSequential(new CmdOutput(1, 1));									//Output cube
//	AddSequential(new CmdAuto_BasicDrive(-0.6, 0, 0.7));				//Drive back a safe distance
//	AddSequential(new CmdArmPosExchange());								//Drop the arm for teleop


	AddParallel(new CmdArmPosSwitch());							//Deploy arm to switch
	AddParallel(new CmdIntakeAuto(2, 1));
	AddSequential(new CmdGyroDrive(5.5, 0), 3.2);					//Deploy arm to switch
	AddParallel(new CmdArmPosScale());							//Raise arm to scale height
	AddSequential(new CmdGyroDrive(0, -55, true, true), 1);		//Turn toward scale
	AddSequential(new CmdGyroDrive(1.3, -45, false, true), 1.7);	//Slowly drive into scale
	AddSequential(new CmdOutput(1,0.5), 0.5);						//Output the cube
	AddParallel(new CmdArmPosGround());							//Drop arm to ground position
	AddSequential(new CmdGyroDrive(-0.5, -45, false, true), 1);	//Drive back a safe distance
}
