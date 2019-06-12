/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/armOutput.h"
#include "Robot.h"

armOutput::armOutput() {}

void armOutput::PIDWrite(double output)
{
    Robot::subEncodedArm->setSpeed(output);
}