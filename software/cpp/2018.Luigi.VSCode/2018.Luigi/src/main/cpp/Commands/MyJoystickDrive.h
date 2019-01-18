#ifndef MYJOYSTICKDRIVE_H
#define MYJOYSTICKDRIVE_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class MyJoystickDrive: public frc::Command {
public:

	MyJoystickDrive();

	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:

};

#endif
