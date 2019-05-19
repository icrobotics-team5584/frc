/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RightVelocitySource.h"
#include "Robot.h"

RightVelocitySource::RightVelocitySource() {}

double RightVelocitySource::PIDGet() {
    return Robot::subDriveBase->getRightVelocity();
}
