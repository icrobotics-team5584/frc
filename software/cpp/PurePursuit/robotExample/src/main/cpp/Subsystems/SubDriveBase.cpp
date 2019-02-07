#include "Subsystems/SubDriveBase.h"
#include "Commands/CmdJoystickDrive.h"
#include "Robot.h"
#include "math.h"

SubDriveBase::SubDriveBase() : Subsystem("ExampleSubsystem") {
  // Copy pointers to the drive base talons into a diff drive
  srxLeft = Robot::robotMap->srxDriveBaseLeft;
  srxRight = Robot::robotMap->srxDriveBaseRight;
  srxLeftSlave = Robot::robotMap->srxDriveBaseLeftSlave;
  srxRightSlave = Robot::robotMap->srxDriveBaseRightSlave;
  diffDrive.reset(new DifferentialDrive(*srxLeft, *srxRight));

  // Copy pointer to the navX
  ahrsNavX = Robot::robotMap->ahrsDriveBaseNavX;

  wheelCircumference = 3.14159265358 * WHEEL_DIAMETER;
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

/*
 * Determines the total distance travelled by the robot since the encoders had last been 
 * zeroed. This is the average distance travelled by both sides of the drive base.
 */
double SubDriveBase::getDistance() {
    double leftSensorUnits = srxLeft->GetSelectedSensorPosition(0);
    double rightSensorUnits = srxRight->GetSelectedSensorPosition(0);

    double aveSensorUnits = (rightSensorUnits-leftSensorUnits)/2; //Minus because left is facing backward
    double rotations = aveSensorUnits/UNITS_PER_ROTATION;
    return (rotations * wheelCircumference);
}

void SubDriveBase::zeroGyro(){
    ahrsNavX->ZeroYaw();
}

void SubDriveBase::zeroEncoders(){
    srxLeft->SetSelectedSensorPosition(0, 0, 20);
    srxRight->SetSelectedSensorPosition(0, 0, 20);
}