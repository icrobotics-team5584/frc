/*
 * armPID.cpp
 *
 *  Created on: 14 Jul. 2018
 *      Author: Liam
 */

#include "armPID.h"
#include "../Robot.h"

armPID::armPID() {
	feedForward = ( (weight * dist) / (gearRatio * (stallTorque/maxVoltage)));
}

void armPID::PIDWrite(double output) {

	// calculate feed forward compensation and apply this
	// note that we need to check that the subsystem is available here before we start calling
	// methods . . . and this happens as the PIDWrite is called during the construction of the
	// PIDController and this will very likely be before the containing object (subsystem) has
	// completed its construction . . . if we fail to do thgis then the program will crash as
	// we are using un-set pointers
	if( Robot::subEncodedArm ) {
		// std::cout << "INFO: subsystem available" << std::endl;
		double currentAngle = Robot::subEncodedArm->GetArmAngle();
		currentAngle = currentAngle*3.1415/180;   // convert to radians
		double additionalVoltage = feedForward * sin(currentAngle) * multiplier;
		double additionalSpeed = additionalVoltage/maxVoltage;
		SmartDashboard::PutNumber("armSpeed", additionalSpeed);
		//Run arm motor with additional speed compensation for gravity
		Robot::subEncodedArm->VoltageControl(output + additionalSpeed);
	} else {
		std::cout << "WARNING: subsystem not yet available - skipping compensation calculation" << std::endl;
	}
}

armPID::~armPID() {
	// TODO Auto-generated destructor stub
}
