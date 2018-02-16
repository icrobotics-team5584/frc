#ifndef SUBDRIVEBASE_H
#define SUBDRIVEBASE_H

#include <ctre/Phoenix.h>
#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <AHRS.h>
#include <EncoderDistanceSource.h>
#include "PIDOutput.h"
#include "PIDSource.h"
#include "PIDController.h"
#include "RobotMap.h"
#include "NavxDriveRotationOutput.h"
#include "NavxDriveSpeedOutput.h"

class SubDriveBase: public frc::Subsystem{
public:
	//DriveModes
	enum DriveMode {Manual, Autonomous};

	SubDriveBase();
	void InitDefaultCommand() override;
	void Periodic() override;
	void AutoDrive(double, double);
	void Stop();
	void TakeJoystickInputs(std::shared_ptr<Joystick>);
	void GyroRotate(double angle);
	void GyroDrive(double distance);
	void ZeroNavX();
	double GetAngle();
	void SetPIDSpeed(double speed);
	void SetPIDRotation(double rotation);
	void HandlePIDOutput(double xSpeed, double zRotation);
	bool ReachedSetPoint();
	void SetDriveMode(DriveMode driveMode);
	void SetEncodersToRelativeZero();
	double GetRelativeDisplacement();

	//Objects used by the Gyro PIDControllers
	static AHRS* navX;
	static double _Speed;
	static double _Rotation;

private:

	DriveMode selectedDriveMode;
	class DriveModeClass {
	public:
		DriveMode myDriveMode;
		DriveModeClass(DriveMode dm){myDriveMode = dm;}
	};
	SendableChooser<DriveModeClass*> driveModeChooser;

	//Drive Wheel Motors
	std::shared_ptr<WPI_TalonSRX> srxLeft;
	std::shared_ptr<WPI_TalonSRX> srxRight;
	std::shared_ptr<frc::DifferentialDrive> differentialDrive;
	const double wheelDiameter = 0.1016; //in meters
	const double wheelCircumference = (wheelDiameter * M_PI);
	const int sensorUnitsPerRotation = 4096;

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

	//NavX objects for autonomous driving
	PIDController* turnController;
	PIDController* driveController;
	NavxDriveRotationOutput* rotationOutput;
	NavxDriveSpeedOutput* speedOutput;

    //Encoder objects for autonomous driving
	EncoderDistanceSource* distanceSource;
	double relativeZero;
};

#endif
