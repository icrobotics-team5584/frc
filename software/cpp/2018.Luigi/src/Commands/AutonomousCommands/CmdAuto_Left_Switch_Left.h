#ifndef CmdAuto_Left_Switch_Left_H
#define CmdAuto_Left_Switch_Left_H

#include <iostream>
#include <Commands/CommandGroup.h>


class CmdAuto_Left_Switch_Left : public CommandGroup {
public:
	CmdAuto_Left_Switch_Left();
	class CmdAuto_IntakeSave : public CommandGroup {
	public:
		CmdAuto_IntakeSave();
	};
};

#endif  // CmdAuto_Left_Switch_Left_H
