/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "ctre/Phoenix.h"

class SubIntake : public frc::Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<WPI_TalonSRX> tnxRight;
	std::shared_ptr<WPI_TalonSRX> tnxLeft;

public:
	SubIntake();
	void InitDefaultCommand() override;
	void In();
	void Out(double speed = 1);
	void Stop();
	void Spin();
};

