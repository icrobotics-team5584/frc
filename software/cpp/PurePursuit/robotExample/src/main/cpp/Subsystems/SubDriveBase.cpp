#include "Subsystems/SubDriveBase.h"
#include "Commands/CmdJoystickDrive.h"
#include "Robot.h"
#include "math.h"

SubDriveBase::SubDriveBase() : Subsystem("ExampleSubsystem") {
  // Copy pointers to the drive base talons
  srxLeft = Robot::robotMap->srxDriveBaseLeft;
  srxRight = Robot::robotMap->srxDriveBaseRight;
  srxLeftSlave = Robot::robotMap->srxDriveBaseLeftSlave;
  srxRightSlave = Robot::robotMap->srxDriveBaseRightSlave;

  // Smoosh talons into a differential drive
  diffDrive.reset(new DifferentialDrive(*srxLeft, *srxRight));

  // Copy pointer to the navX
  ahrsNavX = Robot::robotMap->ahrsDriveBaseNavX;

  // Determine revs per meter
  wheelCircumference = 3.14159265358 * WHEEL_DIAMETER;
  SmartDashboard::PutNumber("wheel circumference", wheelCircumference);
}

void SubDriveBase::InitDefaultCommand() {
  SetDefaultCommand(new CmdJoystickDrive());
}

void SubDriveBase::drive(double speed, double rotation, bool squaredInput) {
  diffDrive->ArcadeDrive(speed, rotation, squaredInput);
}

double SubDriveBase::getAngle() {
    return ahrsNavX->GetYaw();
}

double SubDriveBase::getDistance() {
    double leftSensorUnits = srxLeft->GetSelectedSensorPosition(0);
    double rightSensorUnits = srxRight->GetSelectedSensorPosition(0);

    double aveSensorUnits = (rightSensorUnits-leftSensorUnits)/2; //Minus because left is facing backward
    double rotations = aveSensorUnits/UNITS_PER_ROTATION;
    return (rotations * wheelCircumference);
}


/*
double gearRatio = 10.5;
	double EncoderTicsPerRotation = 80;
	double MetersPerRotation = 0.4787;

	double EncoderTics;
	EncoderTics = tnxBackLeft->GetSelectedSensorPosition(0);
	EncoderTics = EncoderTics/gearRatio;
	double WheelRotations;
	WheelRotations = EncoderTics/EncoderTicsPerRotation;
	double Theamountofmetersgoneby;
	Theamountofmetersgoneby = WheelRotations * MetersPerRotation;


	return Theamountofmetersgoneby;
}
*/


void SubDriveBase::zeroGyro(){
    ahrsNavX->ZeroYaw();
}

void SubDriveBase::zeroEncoders(){
    srxLeft->SetSelectedSensorPosition(0, 0, 20);
    srxRight->SetSelectedSensorPosition(0, 0, 20);
}