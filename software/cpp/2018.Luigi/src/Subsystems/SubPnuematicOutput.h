#ifndef SubPnuematicOutput_H
#define SubPnuematicOutput_H

#include <Commands/Subsystem.h>
#include "WPILib.h"

static std::shared_ptr<DoubleSolenoid> solPusher;

class SubPnuematicOutput : public Subsystem {
private:


public:
	SubPnuematicOutput();
	void InitDefaultCommand();
	void Out();
	void In();
};

#endif  // SubPnuematicOutput_H
