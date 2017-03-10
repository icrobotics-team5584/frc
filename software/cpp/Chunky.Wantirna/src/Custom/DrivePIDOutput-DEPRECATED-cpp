/*
 * DrivePIDOutput.cpp
 *
 *  Created on: 14 Feb 2017
 *      Author: Robocamp
 */

#include "DrivePIDOutput.h"
#include "..\Robot.h"

DrivePIDOutput::DrivePIDOutput(double arg_power){
	power = arg_power;
}

  void DrivePIDOutput::PIDWrite(double output){
	  Robot::subDriveBase->Drive(power, output);
  }

  DrivePIDOutput::~DrivePIDOutput(){
  }
