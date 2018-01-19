#ifndef SubEncodedArmLift_H
#define SubEncodedArmLift_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <ctre/Phoenix.h>
#include "Constants.h"
#include <SmartDashboard/SmartDashboard.h>


class SubEncodedArmLift : public Subsystem {
private:


	int TWO;
	int THREE;
	int FOUR;

	std::shared_ptr<WPI_TalonSRX> _talon;
	std::string _sb;
	Preferences *_prefs;
	int _loops = 0;
	double targetPositionRotations;
	int absolutePosition;



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
