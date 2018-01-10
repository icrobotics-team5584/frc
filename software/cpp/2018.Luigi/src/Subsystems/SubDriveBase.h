#ifndef SubDriveBase_H
#define SubDriveBase_H

#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <wpilib.h>

std::shared_ptr<WPI_TalonSRX> tnxLeftDriveMaster;
std::shared_ptr<WPI_TalonSRX> tnxLeftDriveSlave;
std::shared_ptr<WPI_TalonSRX> tnxRightDriveMaster;
std::shared_ptr<WPI_TalonSRX> tnxRightDriveSlave;

std::shared_ptr<DifferentialDrive> differentialDrive;

class SubDriveBase : public Subsystem {
private:


public:
	SubDriveBase();
	void InitDefaultCommand();
	void TakeJoystickInputs(std::shared_ptr<Joystick>);
	void Drive(double, double);
	void Stop();
};

#endif  // SubDriveBase_H
