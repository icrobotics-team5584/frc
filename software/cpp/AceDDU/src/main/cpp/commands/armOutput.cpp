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
    _angle = output - _top;

    _angleDeg = _angle / (4096) * 360;

    frc::SmartDashboard::PutNumber("Actual Arm Angle", _angleDeg);

    _angleRad = _angleDeg * pi/180;

    _outputSpeed = sin(_angleRad) * multiplier;

    Robot::subEncodedArm->setSpeed(_outputSpeed);
}