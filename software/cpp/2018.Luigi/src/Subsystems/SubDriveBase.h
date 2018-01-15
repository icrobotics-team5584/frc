#ifndef SUBDRIVEBASE_H
#define SUBDRIVEBASE_H

#include <ctre/Phoenix.h>
#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <SmartDashboard/SmartDashboard.h>

#include "RobotMap.h"


class SubDriveBase: public frc::Subsystem {
private:
	std::shared_ptr<WPI_TalonSRX> sRXleft;
	std::shared_ptr<WPI_TalonSRX> sRXright;
	std::shared_ptr<frc::DifferentialDrive> differentialDrive;

	std::shared_ptr<frc::AnalogInput> ultrasonicInputFront;
	std::shared_ptr<frc::AnalogInput> ultrasonicInputRight;
	std::shared_ptr<frc::AnalogInput> ultrasonicInputBack;
	std::shared_ptr<frc::AnalogInput> ultrasonicInputLeft;

public:
	SubDriveBase();
	void InitDefaultCommand() override;
	void Periodic() override;
	void AutoDrive(double, double);
	void Stop();
	void TakeJoystickInputs(std::shared_ptr<Joystick>);

};

#endif
