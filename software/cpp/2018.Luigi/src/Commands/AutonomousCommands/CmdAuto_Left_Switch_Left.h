#ifndef CmdAuto_Left_Switch_Left_H
#define CmdAuto_Left_Switch_Left_H

#include <Commands/CommandGroup.h>
#include "Robot.h"
#include "Commands/AutonomousCommands/CmdAuto_MotionProfile.h"
#include "Commands/CmdArmPosSwitch.h"

class CmdAuto_Left_Switch_Left : public CommandGroup {
public:
	CmdAuto_Left_Switch_Left();
};

#endif  // CmdAuto_Left_Switch_Left_H
