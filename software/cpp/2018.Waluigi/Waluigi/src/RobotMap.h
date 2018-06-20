#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "WPILib.h"
#include "ctre/Phoenix.h"

class RobotMap {
public:
	//Drive Base
	static std::shared_ptr<WPI_TalonSRX> subDriveBaseTnxFrontRight;
	static std::shared_ptr<WPI_TalonSRX> subDriveBaseTnxFrontLeft;
	static std::shared_ptr<frc::DifferentialDrive> subDriveBaseDifDrive;
	static std::shared_ptr<WPI_TalonSRX> subDriveBaseTnxBackLeft;
	static std::shared_ptr<WPI_TalonSRX> subDriveBaseTnxBackRight;

	//InTake
	static std::shared_ptr<WPI_TalonSRX> subIntakeTnxLeft;
	static std::shared_ptr<WPI_TalonSRX> subIntakeTnxRight;

	//EncodedArm
	static std::shared_ptr<WPI_TalonSRX> subEncodedArmTnx;
	static std::shared_ptr<AnalogInput> subEncodedArmPot;

	static void init();
};
#endif
