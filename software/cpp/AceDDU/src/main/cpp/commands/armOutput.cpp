/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/armOutput.h"
#include "Robot.h"

armOutput::armOutput() {

    subEncodedArm.reset(new SubEncodedArm);
}

void armOutput::PIDWrite(double output)
{

    _angleRad = subEncodedArm->getAngle() * (pi/180);


    _outputSpeed = (sin(_angleRad) * multiplier) + output;

    /* REMOVE THIS LINE WHEN YOU ARE SURE THAT ANGLE RETURNED IS
    ZERO DEGREES FOR ARM IN VERTICAL UP POSITION */
    _outputSpeed = 0;

    frc::SmartDashboard::PutNumber("Output Speed", _outputSpeed);

    Robot::subEncodedArm->setSpeed(_outputSpeed);
}