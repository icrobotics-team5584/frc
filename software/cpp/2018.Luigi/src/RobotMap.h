#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "WPILib.h"
#include "ctre/Phoenix.h"


class RobotMap {
public:
	static std::shared_ptr<WPI_TalonSRX> subDriveBaseSRXleft;
	static std::shared_ptr<WPI_TalonSRX> subDriveBaseSRXright;
	static std::shared_ptr<frc::DifferentialDrive> subDriveBaseMyFirstDifferentialDrive;

	static std::shared_ptr<WPI_TalonSRX> subDriveBaseSRXleftSlave;
	static std::shared_ptr<WPI_TalonSRX> subDriveBaseSRXrightSlave;

	static std::shared_ptr<WPI_TalonSRX> subIntakeTnxRight;
	static std::shared_ptr<WPI_TalonSRX> subIntakeTnxLeft;
	static void init();
};
#endif
