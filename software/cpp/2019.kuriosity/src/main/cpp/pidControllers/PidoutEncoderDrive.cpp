/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "pidControllers/PidoutEncoderDrive.h"
#include "Robot.h"

PidoutEncoderDrive::PidoutEncoderDrive() {}

void PidoutEncoderDrive::PIDWrite(double output) {
    //frc::SmartDashboard::PutNumber("PID Output", output);
    Robot::subDriveBase->drive(output, 0);
}