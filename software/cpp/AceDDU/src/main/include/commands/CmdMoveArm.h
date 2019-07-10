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
#include "subsystems/SubEncodedArm.h"
//#include "Robot.h"
#include "commands/armOutput.h"
#include "PidsrcArm.h"

class CmdMoveArm : public frc::Command
{
  public:
	CmdMoveArm();
	double PIDGet();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

	void setTicks(int ticks);
  	void setAngle(double angle);
	//virtual ~PIDMag();
  private:
	frc::PIDController *armController;

	armOutput _armOutput;
	PidsrcArm _pidsrcArm;
	double EncBack = 0;
	double EncFront = 4096;
	//double PotUp = 1435;
	double totalAngle = 90;
	double PIDp = -0.0002;
	double PIDi = 0.0;
	double PIDd = -0.0005;

	double _armTicks;
  	double _relativeArmTicks;
  	double _zeroPoint = 2200;
};

//#endif /* SRC_SUBSYSTEMS_PIDPOT_H_ */
