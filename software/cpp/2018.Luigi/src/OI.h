#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	std::shared_ptr<frc::Joystick> joystick0;
	std::shared_ptr<JoystickButton> btnIntake;
	std::shared_ptr<JoystickButton> btnOutput;

public:
	OI();
	std::shared_ptr<frc::Joystick> getJoystick0();
};

#endif
