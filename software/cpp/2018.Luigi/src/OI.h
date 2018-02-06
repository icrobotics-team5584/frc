#ifndef OI_H
#define OI_H

#include <WPILib.h>
#include <SmartDashboard/SmartDashboard.h>


class OI {
private:
	std::shared_ptr<frc::Joystick> joystick0;
	std::shared_ptr<JoystickButton> btnIntake;
	std::shared_ptr<JoystickButton> btnOutput;
	std::shared_ptr<JoystickButton> btnArmToGround;
	std::shared_ptr<JoystickButton> btnArmToSwitch;
	std::shared_ptr<JoystickButton> btnArmToScale;
	std::shared_ptr<JoystickButton> btnArmToExchange;
	std::shared_ptr<JoystickButton> btnArmOveride;
	std::shared_ptr<JoystickButton> btnEncoderPosReset;
	std::shared_ptr<JoystickButton> btnMP;
	std::shared_ptr<JoystickButton> btnChangeCamera;

public:
	OI();
	std::shared_ptr<frc::Joystick> getJoystick0();
};

#endif
