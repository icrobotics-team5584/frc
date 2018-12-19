#ifndef CmdAuto_BasicDrive_H
#define CmdAuto_BasicDrive_H

#include "Commands/Command.h"
#include "Robot.h"

class CmdAuto_BasicDrive : public Command {
public:
	CmdAuto_BasicDrive(double speed, double rotation, double time);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	double _speed;
	double _rotation;
	double _time;
};

#endif  // CmdAuto_BasicDrive_H
