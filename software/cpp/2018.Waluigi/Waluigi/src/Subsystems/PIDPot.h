/*
 * PIDPot.h
 *
 *  Created on: 23 Jun. 2018
 *      Author: User
 */

#pragma once

//#ifndef SRC_SUBSYSTEMS_PIDPOT_H_
//#define SRC_SUBSYSTEMS_PIDPOT_H_

#include "WPILib.h"

class PIDPot : public PIDSource {
public:
	PIDPot();
	double PIDGet();
	virtual ~PIDPot();
private:
	std::shared_ptr<AnalogInput> _potMain;

};

//#endif /* SRC_SUBSYSTEMS_PIDPOT_H_ */
