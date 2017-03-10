/*
 * TurnPIDOutput.cpp
 *
 *  Created on: 21 Feb 2017
 *      Author: Robocamp
 */

#include "TurnPIDOutput.h"
#include "..\Robot.h"

TurnPIDOutput::TurnPIDOutput(double arg_power){
	power = arg_power;
}

  void TurnPIDOutput::PIDWrite(double output){
	  Robot::subDriveBase->Drive(output * power, 1);
  }

  TurnPIDOutput::~TurnPIDOutput(){
  }


