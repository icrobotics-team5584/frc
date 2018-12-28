#include "Subsystems/SubDriveBase.h"
#include "Commands/CmdJoystickDrive.h"
#include "Robot.h"

SubDriveBase::SubDriveBase() : Subsystem("ExampleSubsystem") {
  // Copy pointers to the drive base talons
  srxLeft = Robot::robotMap->srxDriveBaseLeft;
  srxRight = Robot::robotMap->srxDriveBaseRight;
  srxLeftSlave = Robot::robotMap->srxDriveBaseLeftSlave;
  srxRightSlave = Robot::robotMap->srxDriveBaseRightSlave;

  // Copy pointer to the navX
  ahrsNavX = Robot::robotMap->ahrsDriveBaseNavX;

  // Smoosh talons into a differential drive
  scgLeft.reset(new SpeedControllerGroup{*srxLeft, *srxLeftSlave});
  scgRight.reset(new SpeedControllerGroup{*srxRight, *srxRightSlave});
  diffDrive.reset(new DifferentialDrive(*scgLeft, *scgRight));
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
    return (srxLeft->GetSelectedSensorPosition(0) + srxRight->GetSelectedSensorPosition(0))/2;
}