#ifndef SubEncodedArmLift_H
#define SubEncodedArmLift_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <ctre/Phoenix.h>
#include "Constants.h"
#include <SmartDashboard/SmartDashboard.h>


class SubEncodedArmLift : public Subsystem {
private:


	std::shared_ptr<DigitalInput> _swtBottomReset;
	std::shared_ptr<WPI_TalonSRX> _talon;
	std::string _sb;
	Preferences *_prefs;
	int _loops = 0;
	int _axisLoops = 0;
	double targetPositionRotations;
	int absolutePosition = 0;
	double _axis = 0;

public:
	SubEncodedArmLift();
	void ArmToGroundPos();
	void ArmToSwitchPos();
	void ArmToScalePos();
	void ArmToExchangePos();
	void Overide(std::shared_ptr<Joystick>);
	void Periodic();
	void Reset();

};

#endif  // SubEncodedArmLift_H
