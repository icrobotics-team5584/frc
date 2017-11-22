#ifndef CmdCameraTrack_H
#define CmdCameraTrack_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class CmdCameraTrack : public Command {
public:
	CmdCameraTrack();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif  // CmdCameraTrack_H
