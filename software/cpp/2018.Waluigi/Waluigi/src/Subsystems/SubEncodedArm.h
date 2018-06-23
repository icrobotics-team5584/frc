

#pragma once

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include <ctre/phoenix.h>
#include <SmartDashboard/SmartDashboard.h>

class SubEncodedArm : public frc::Subsystem {
private:

	std::shared_ptr<WPI_TalonSRX> _talon;
	std::shared_ptr<AnalogInput> _potMain;

	PIDController* armController;

	int  lc = 0;
	double _axis5 = 0.0;

	int PotBack = 152;
	int PotFront = 2346;
	int totalAngle = 190;


public:
	SubEncodedArm();
	void InitDefaultCommand() override;
	void Periodic();
	void Stop();
	void ArmJoyMove(std::shared_ptr<frc::Joystick> controller);
	void PIDToggle();
	void PIDArmTo(int angle);
};

