#ifndef CmdAuto_BasicDrive_H
#define CmdAuto_BasicDrive_H

#include "Commands/Command.h"
#include "Robot.h"

class CmdAuto_BasicDrive : public Command {
public:
	CmdAuto_BasicDrive(double speed, double rotation);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	double _speed;
	double _rotation;
};

#endif  // CmdAuto_BasicDrive_H
