/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Subsystem.h>
#include <ctre/phoenix.h>
#include <WPILib.h>

class SubFinger : public frc::Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	std::shared_ptr<VictorSP> _fingerSP;
	std::shared_ptr<DigitalInput> _fingerUpSwt;
	int _switchCase;

public:
	SubFinger();
	void InitDefaultCommand() override;
	void FingerUp();
	void FingerDown();
	void FingerStop();
	void FingerDefaultStop();
	bool GetSwitches();
	int GetSwitchCase();
};

