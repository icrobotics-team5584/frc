#ifndef OI_H
#define OI_H

#include <WPILib.h>
#include <SmartDashboard/SmartDashboard.h>
#include "AxisButton.h"

class OI {
private:
	std::shared_ptr<frc::Joystick> joystick0;
	std::shared_ptr<JoystickButton> btnIntake;
	std::shared_ptr<AxisButton> axsOutput;
	std::shared_ptr<JoystickButton> btnOutput;
	std::shared_ptr<JoystickButton> btnArmToGround;
	std::shared_ptr<JoystickButton> btnArmToSwitch;
	std::shared_ptr<JoystickButton> btnArmToScale;
	std::shared_ptr<JoystickButton> btnArmToScaleLow;
	std::shared_ptr<JoystickButton> btnArmToExchange;
	std::shared_ptr<JoystickButton> btnArmOveride;
	std::shared_ptr<JoystickButton> btnEncoderPosReset;
	std::shared_ptr<JoystickButton> btnMP;
	std::shared_ptr<JoystickButton> btnChangeCamera;
	std::shared_ptr<JoystickButton> DropRampClamp;

public:
	OI();
	std::shared_ptr<frc::Joystick> getJoystick0();
};

#endif
