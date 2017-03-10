/*
 * DrivePIDOutput.h
 *
 *  Created on: 14 Feb 2017
 *      Author: Robocamp
 */

#ifndef SRC_CUSTOM_DRIVEPIDOUTPUT_H_
#define SRC_CUSTOM_DRIVEPIDOUTPUT_H_

#include "PIDOutput.h"

class DrivePIDOutput: public frc::PIDOutput {

public:
	DrivePIDOutput(double arg_power);
	virtual ~DrivePIDOutput();
	virtual void PIDWrite(double output);

private:
	double power = 0;
};


#endif /* SRC_CUSTOM_DRIVEPIDOUTPUT_H_ */
