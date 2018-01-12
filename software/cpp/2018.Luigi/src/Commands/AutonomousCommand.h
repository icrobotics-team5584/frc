#ifndef AUTONOMOUS_COMMAND_H
#define AUTONOMOUS_COMMAND_H


#include "Commands/Subsystem.h"
#include "../Robot.h"

class AutonomousCommand: public frc::Command {
public:
	AutonomousCommand();

	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:

};

#endif
