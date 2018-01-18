#ifndef SubEncodedArmLift_H
#define SubEncodedArmLift_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <ctre/Phoenix.h>
#include "Constants.h"
#include <SmartDashboard/SmartDashboard.h>


class SubEncodedArmLift : public Subsystem {
private:

	std::shared_ptr<WPI_TalonSRX> _talon;
	std::shared_ptr<Joystick> _joy;
	std::shared_ptr<Joystick> _joyTemp;
	std::string _sb;
	Preferences *_prefs;
	double _groundTarget;
	double _switchTarget;
	double _scaleTarget;
	int _loops = 0;
	bool _lastButton1 = false;
	double targetPositionRotations;
	int absolutePosition;

	double leftYstick;
	double motorOutput;
	bool button1;
	bool button2;

public:
	SubEncodedArmLift();
	void ArmToGroundPos();
	void ArmToSwitchPos();
	void ArmToScalePos();
	void Periodic();
	void InitDefaultCommand();
	void TakeJoystickInputs(std::shared_ptr<Joystick>);
};

#endif  // SubEncodedArmLift_H
