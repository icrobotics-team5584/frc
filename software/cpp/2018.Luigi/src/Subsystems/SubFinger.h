/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

//#pragma once

#ifndef SubFinger_H
#define SubFinger_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <ctre/phoenix.h>

class SubFinger : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	std::shared_ptr<VictorSP> _fingerSP;
	std::shared_ptr<DigitalInput> _fingerUpSwt;
	int _switchCase = 0;

public:
	SubFinger();
	//void InitDefaultCommand();
	void FingerUp();
	void FingerDown();
	void FingerStop();
	void FingerDefaultStop();
	bool GetSwitches();
	int GetSwitchCase();
};

#endif  // SubFinger_H
