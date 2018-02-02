#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "AHRS.h"
#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "MotionProfileData.h"
#include "MotionProfiles/MotionProfileBaselineA.h"
#include "MotionProfiles/MotionProfileBaselineB.h"
#include "MotionProfiles/MPL-test.h"
#include "MotionProfiles/MPR-test.h"


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
	static std::shared_ptr<WPI_TalonSRX> subIntakeTnxBottom;
	static std::shared_ptr<DigitalInput> subIntakeSwtLeftLimit;
	static std::shared_ptr<DigitalInput> subIntakeSwtRightLimit;



//	//Define anlouge Ultrasonic sensors
//	static std::shared_ptr<frc::AnalogInput> subDriveBaseUltrasonicInputFront;
//	static std::shared_ptr<frc::AnalogInput> subDriveBaseUltrasonicInputRight;
//	static std::shared_ptr<frc::AnalogInput> subDriveBaseUltrasonicInputBack;
//	static std::shared_ptr<frc::AnalogInput> subDriveBaseUltrasonicInputLeft;

	//Define echo ultrasonic sensors
	static std::shared_ptr<frc::Ultrasonic> subDriveBaseUltrasonicInputFront;
	static std::shared_ptr<frc::Ultrasonic> subDriveBaseUltrasonicInputRight;
	static std::shared_ptr<frc::Ultrasonic> subDriveBaseUltrasonicInputBack;
	static std::shared_ptr<frc::Ultrasonic> subDriveBaseUltrasonicInputLeft;

	//Define arm lift Actuators / Actuator
	static std::shared_ptr<WPI_TalonSRX> subEncodedArmLiftSrxMaster;
	static std::shared_ptr<WPI_TalonSRX> subEncodedArmLiftSrxSlave;
	static std::shared_ptr<DigitalInput> subEncodedArmLiftSwtBottom;

	
	//Define Motion Profile Data
	static std::shared_ptr<MotionProfileData> mpBaseline;
	static std::shared_ptr<MotionProfileData> mpTest;

	//Define micro navX gyro
	static std::shared_ptr<AHRS> ahrsGyro;


};
#endif
