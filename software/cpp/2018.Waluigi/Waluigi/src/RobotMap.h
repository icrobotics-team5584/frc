#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "WPILib.h"
#include "ctre/Phoenix.h"

class RobotMap {
public:
	static std::shared_ptr<WPI_TalonSRX> subDriveBaseTnxFrontRight;
	static std::shared_ptr<WPI_TalonSRX> subDriveBaseTnxFrontLeft;
	static std::shared_ptr<frc::DifferentialDrive> subDriveBaseDifDrive;
	static std::shared_ptr<WPI_TalonSRX> subDriveBaseTnxBackLeft;
	static std::shared_ptr<WPI_TalonSRX> subDriveBaseTnxBackRight;

	static void init();
};
#endif
