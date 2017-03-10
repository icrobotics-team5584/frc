/*
 * TurnPIDOutput.h
 *
 *  Created on: 21 Feb 2017
 *      Author: Robocamp
 */

#ifndef SRC_CUSTOM_TURNPIDOUTPUT_H_
#define SRC_CUSTOM_TURNPIDOUTPUT_H_

#include "PIDOutput.h"

class TurnPIDOutput: public frc::PIDOutput {

public:
	TurnPIDOutput(double arg_power);
	virtual ~TurnPIDOutput();
	virtual void PIDWrite(double output);

private:
	double power;
};




#endif /* SRC_CUSTOM_TURNPIDOUTPUT_H_ */
