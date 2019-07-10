/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "PidsrcArm.h"
#include "Robot.h"

PidsrcArm::PidsrcArm() {
}

double PidsrcArm::PIDGet(){
    return Robot::subEncodedArm->getEncoder();
}