/*
 * armPID.h
 *
 *  Created on: 14 Jul. 2018
 *      Author: Liam
 */

#ifndef SRC_SUBSYSTEMS_ARMPID_H_
#define SRC_SUBSYSTEMS_ARMPID_H_

#include "WPILib.h"

class armPID : public PIDOutput {
public:
	armPID();
	void PIDWrite(double output);
	virtual ~armPID();

private:

	double feedForward;
	double multiplier = 1.3;

	//Arm constants
	const double dist =             0.54;   //Meters
	const double weight =           5;              //Kilograms

	//Motor constants
	const double stallTorque =      1.4;    //Newton Meters
	const double maxVoltage =       12;             //Volts

	//GearBox constants
	const double gearRatio =        10.5;

};

#endif /* SRC_SUBSYSTEMS_ARMPID_H_ */
