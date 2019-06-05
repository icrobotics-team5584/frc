/*
 * PIDPot.h
 *
 *  Created on: 23 Jun. 2018
 *      Author: User
 */

#pragma once

//#ifndef SRC_SUBSYSTEMS_PIDPOT_H_
//#define SRC_SUBSYSTEMS_PIDPOT_H_

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <frc/WPILib.h>

class PIDMag : public frc::PIDSource {
public:
	PIDMag();
	std::shared_ptr<WPI_TalonSRX> srxArm;
	double PIDGet();
	virtual ~PIDMag();
	int get_armPos();
private:

};

//#endif /* SRC_SUBSYSTEMS_PIDPOT_H_ */
