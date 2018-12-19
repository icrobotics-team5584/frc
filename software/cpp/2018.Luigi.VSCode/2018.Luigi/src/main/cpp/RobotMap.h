#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "AHRS.h"
#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "Autonomous/MotionProfileData.h"


class RobotMap {
public:
	static void init();

	//Define DriveBase Actuators and Sensors
	static std::shared_ptr<WPI_TalonSRX> subDriveBaseSRXleft;
	static std::shared_ptr<WPI_TalonSRX> subDriveBaseSRXright;
	static std::shared_ptr<frc::DifferentialDrive> subDriveBaseDifferentialDrive;
	static std::shared_ptr<WPI_TalonSRX> subDriveBaseSRXleftSlave;
	static std::shared_ptr<WPI_TalonSRX> subDriveBaseSRXrightSlave;

	//Define Intake Actuators and Sensors
	static std::shared_ptr<WPI_TalonSRX> subIntakeTnxRight;
	static std::shared_ptr<WPI_TalonSRX> subIntakeTnxLeft;
	static std::shared_ptr<VictorSP> subIntakeSpFinger;
	static std::shared_ptr<DigitalInput> subIntakeSwtFingerUp;
	static std::shared_ptr<DigitalInput> subIntakeSwtLeftLimit;
	static std::shared_ptr<DigitalInput> subIntakeSwtRightLimit;


	//Define arm lift Actuators / Actuator
	static std::shared_ptr<WPI_TalonSRX> subEncodedArmLiftSrxMaster;
	static std::shared_ptr<WPI_TalonSRX> subEncodedArmLiftSrxSlave;
	static std::shared_ptr<DigitalInput> subEncodedArmLiftSwtTop;
	static std::shared_ptr<DigitalInput> subEncodedArmLiftSwtTopSecondary;
	static std::shared_ptr<DigitalInput> subEncodedArmLiftSwtBottom;

	//Define Ramp drop actuator
	static std::shared_ptr<VictorSP> subRampSPLeft;

	//Define micro navX gyro
	static std::shared_ptr<AHRS> navX;
};
#endif
