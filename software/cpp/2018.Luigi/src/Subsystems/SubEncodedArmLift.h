#ifndef SubEncodedArmLift_H
#define SubEncodedArmLift_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <ctre/Phoenix.h>
#include "Constants.h"
#include <SmartDashboard/SmartDashboard.h>


class SubEncodedArmLift : public Subsystem {
private:


	std::shared_ptr<DigitalInput> _swtTopStop;
	std::shared_ptr<WPI_TalonSRX> _talon;
	int _loops = 0;
	int _axisLoops = 0;
	double targetPositionRotations;
	int absolutePosition = 0;
	double _axis = 0;
	int _test = 0;
	double _tempStore = 0;

public:
	SubEncodedArmLift();
	void ArmToGroundPos();
	void ArmToSwitchPos();
	void ArmToScalePos();
	void ArmToExchangePos();
	void Overide(std::shared_ptr<Joystick>);
	bool GetSwitches();
	void Reset();
	void Stop();
	void DefaultStop();
	void InitDefaultCommand();

};

#endif  // SubEncodedArmLift_H
