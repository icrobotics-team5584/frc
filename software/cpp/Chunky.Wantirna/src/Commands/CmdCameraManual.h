#ifndef CmdCameraManual_H
#define CmdCameraManual_H

#include "Commands/Subsystem.h"
#include "../Robot.h"
#include "WPILib.h"

class CmdCameraManual : public Command {
public:
	CmdCameraManual();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdCameraManual_H
