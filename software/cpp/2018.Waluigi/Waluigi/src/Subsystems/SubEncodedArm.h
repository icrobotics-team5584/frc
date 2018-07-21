
#pragma once

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include <ctre/phoenix.h>
#include <SmartDashboard/SmartDashboard.h>
#include <iostream>
#include "PIDPot.h"
#include "armPID.h"

class SubEncodedArm : public frc::Subsystem {
private:

	std::shared_ptr<WPI_TalonSRX> _talon;
	std::shared_ptr<AnalogInput> _potMain;

	PIDController* armController;
	PIDPot* _potSourcePID;
	armPID* _armOutputPID;

	int  lc = 0;
	double _axis5 = 0.0;

	double PotBack = 2500;
	double PotFront = 440;
	double PotUp = 1435;
	double totalAngle = 180;
	double PIDp = 0.0007;
	double PIDi = 0.0;
	double PIDd = 0.0;

public:
	SubEncodedArm();
	void InitDefaultCommand() override;
	void Periodic();
	void Stop();
	void ArmJoyMove(std::shared_ptr<frc::Joystick> controller);
	void VoltageControl(double percentage);
	double GetArmAngle();
	void PIDToggle();
	void PIDEnable();
	void PIDDisable();
	void PIDArmTo(int angle);
};
