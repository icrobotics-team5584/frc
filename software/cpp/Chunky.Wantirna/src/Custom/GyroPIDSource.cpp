/*
 * GyroPIDSource.cpp
 *
 *  Created on: 14 Feb 2017
 *      Author: Robocamp
 */

#include "GyroPIDSource.h"
#include "..\Robot.h"

	GyroPIDSource::GyroPIDSource() {


	}

	GyroPIDSource::~GyroPIDSource(){

	}

	double GyroPIDSource::PIDGet() {
	double angle = Robot::subDriveBase->GetAngle();
	// always get a value between -180 and 180 degrees
	while (angle > 180)
	{
		angle -= 360;
	}
	while (angle < -180)
	{
		angle += 360;
	}
	//Return value between -0.5 and 0.5
	return angle/360;
	}
