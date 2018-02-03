#ifndef CmdAuto_Left_Switch_Left_H
#define CmdAuto_Left_Switch_Left_H

#include <iostream>
#include <Commands/CommandGroup.h>
#include "CmdAuto_MotionProfile.h"
#include "Commands/CmdArmPosSwitch.h"
#include "Commands/CmdOutput.h"

class CmdAuto_Left_Switch_Left : public CommandGroup {
public:
	CmdAuto_Left_Switch_Left();
};

#endif  // CmdAuto_Left_Switch_Left_H
