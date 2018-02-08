#ifndef CmdAuto_Left_Scale_Left_H
#define CmdAuto_Left_Scale_Left_H

#include <Commands/CommandGroup.h>

class CmdAuto_Left_Scale_Left : public CommandGroup {
public:
	CmdAuto_Left_Scale_Left();

	class CmdAuto_DelayedLift : public CommandGroup {
	public:
		CmdAuto_DelayedLift();
	};
};

#endif  // CmdAuto_Left_Scale_Left_H
