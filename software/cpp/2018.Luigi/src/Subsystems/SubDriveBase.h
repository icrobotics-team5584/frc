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

	//This is for anlouge ultras
//	std::shared_ptr<frc::AnalogInput> ultrasonicInputFront;
//	std::shared_ptr<frc::AnalogInput> ultrasonicInputRight;
//	std::shared_ptr<frc::AnalogInput> ultrasonicInputBack;
//	std::shared_ptr<frc::AnalogInput> ultrasonicInputLeft;

	//this is for echo ultras
	std::shared_ptr<frc::Ultrasonic> ultrasonicInputFront;
	std::shared_ptr<frc::Ultrasonic> ultrasonicInputRight;
	std::shared_ptr<frc::Ultrasonic> ultrasonicInputBack;
	std::shared_ptr<frc::Ultrasonic> ultrasonicInputLeft;

	int _Ultraloops = 0;
	int frontUValue = 0;
	int rightUValue = 0;
	int backUValue = 0;
	int leftUValue = 0;

public:
	SubDriveBase();
	void InitDefaultCommand() override;
	void Periodic() override;
	void AutoDrive(double, double);
	void Stop();
	void TakeJoystickInputs(std::shared_ptr<Joystick>);
	void ZeroDriveEncoders();
	void ClearMPBuffers();

};

#endif
