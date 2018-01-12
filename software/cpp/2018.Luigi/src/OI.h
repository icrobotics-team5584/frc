/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

//#pragma once

#ifndef OI_H
#define OI_H

#include <WPILib.h>

class OI {

private:

	std::shared_ptr<Joystick> joystick1;

public:

	std::shared_ptr<Joystick> GetJoystick1();
	OI();
};

#endif
