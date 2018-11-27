#include "Subsystems/SubDriveBase.h"
#include "Commands/CmdJoystickDrive.h"
#include "Robot.h"

SubDriveBase::SubDriveBase() : Subsystem("ExampleSubsystem") {
  // Copy pointers to the drive base talons
  srxLeft = Robot::robotMap->srxDriveBaseLeft;
  srxRight = Robot::robotMap->srxDriveBaseRight;
  srxLeftSlave = Robot::robotMap->srxDriveBaseLeftSlave;
  srxRightSlave = Robot::robotMap->srxDriveBaseRightSlave;

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