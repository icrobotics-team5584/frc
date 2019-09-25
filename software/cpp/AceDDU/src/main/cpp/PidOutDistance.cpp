/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "PidOutDistance.h"
#include<frc/WPILib.h>
#include <Robot.h>

PidOutDistance::PidOutDistance() {}

void PidOutDistance::PIDWrite(double output){
    Robot::subDrivebase->drive(output,0);
}