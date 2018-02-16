#pragma once

#include <WPILib.h>

class NavxDriveSpeedOutput : public PIDOutput{
public:
	NavxDriveSpeedOutput();
	void PIDWrite(double xSpeed);
	virtual ~NavxDriveSpeedOutput();
};
