#ifndef SUBDRIVEBASE_H
#define SUBDRIVEBASE_H

#include <ctre/Phoenix.h>
#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <AHRS.h>
#include <Autonomous/DrivePID/EncoderDistanceSource.h>
#include "PIDOutput.h"
#include "PIDSource.h"
#include "PIDController.h"
#include "RobotMap.h"
#include "Autonomous/DrivePID/NavxDriveRotationOutput.h"
#include "Autonomous/DrivePID/NavxDriveSpeedOutput.h"

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
	void GyroDrive(double distance, double maxPower);
	void ZeroNavX();
	void ZeroEncoders();
	void ClearMPBuffers();
	void SetPIDSpeed(double speed);
	void SetPIDRotation(double rotation);
	void SetPIDIsQuickTurn(bool isQuickTurn);
	void SetDrivePIDVals(double p, double i, double d);
	void HandlePIDOutput(double xSpeed, double zRotation, bool isQuickTurn);
	void SetDriveMode(DriveMode driveMode);
	bool ReachedSetPoint();
	double GetEncoderDistance();
	double GetAngle();

private:

	DriveMode selectedDriveMode;

	//Drive Wheel Motors
	std::shared_ptr<WPI_TalonSRX> srxLeft;
	std::shared_ptr<WPI_TalonSRX> srxRight;
	std::shared_ptr<frc::DifferentialDrive> differentialDrive;
	const double wheelDiameter = 0.1016; //in meters
	const double wheelCircumference = (wheelDiameter * M_PI);
	const int sensorUnitsPerRotation = 4096;


	//NavX objects for autonomous driving
	PIDController* turnController;
	PIDController* driveController;
	NavxDriveRotationOutput* rotationOutput;
	NavxDriveSpeedOutput* speedOutput;

    //Encoder objects for autonomous driving
	EncoderDistanceSource* distanceSource;
	double relativeZero;

	//Objects used by the Gyro PIDControllers
	AHRS* navX;
	double _Speed;
	double _Rotation;
	bool _isQuickTurn;
};

#endif
