#ifndef CmdCameraTrack_H
#define CmdCameraTrack_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class CmdCameraTrack : public Command {
public:
	CmdCameraTrack();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdCameraTrack_H
