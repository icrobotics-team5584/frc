#ifndef OI_H
#define OI_H

#include "WPILib.h"



class OI {
private:
	std::shared_ptr<frc::Joystick> joystick0;
	std::shared_ptr<JoystickButton> btnIntake;
	std::shared_ptr<JoystickButton> btnOutput;
	std::shared_ptr<JoystickButton> btnArmUp;
	std::shared_ptr<JoystickButton> btnArmDown;
	std::shared_ptr<JoystickButton> btnArmToGround;
	std::shared_ptr<JoystickButton> btnArmToSwitch;
	std::shared_ptr<JoystickButton> btnArmToScale;
	std::shared_ptr<JoystickButton> btnMP;

public:
	OI();
	std::shared_ptr<frc::Joystick> getJoystick0();
};

#endif
