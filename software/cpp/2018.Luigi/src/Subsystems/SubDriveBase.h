#ifndef SUBDRIVEBASE_H
#define SUBDRIVEBASE_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class SubDriveBase: public frc::Subsystem {
private:
	std::shared_ptr<WPI_TalonSRX> sRXleft;
	std::shared_ptr<WPI_TalonSRX> sRXright;
	std::shared_ptr<frc::DifferentialDrive> differentialDrive;

public:
	SubDriveBase();
	void InitDefaultCommand() override;
	void Periodic() override;
	void TakeJoystickInputs(std::shared_ptr<Joystick>);

};

#endif
