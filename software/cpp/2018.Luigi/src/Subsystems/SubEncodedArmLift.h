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
	std::shared_ptr<DigitalInput> _swtBottomStop;
	std::shared_ptr<WPI_TalonSRX> _talon;
	double targetPositionRotations;
	double _axis5 = 0;
	double _axis3 = 0;
	double _btn7 = 0;
	int overideCase = 0;
	int overideSpeed = 0;
	int swtCase = 0;
	int stopCase = 0;


public:
	SubEncodedArmLift();
	void ArmToGroundPos();
	void ArmToSwitchPos();
	void ArmToScalePos();
	void ArmToExchangePos();
	void Overide(std::shared_ptr<Joystick>);
	bool GetSwitches();
	void Reset();
	void StartBtnReset();
	void Stop();
	int GetSwtCase();
	void IfBottom();
	void IfTop();
	void MovementCheck();

};

#endif  // SubEncodedArmLift_H
