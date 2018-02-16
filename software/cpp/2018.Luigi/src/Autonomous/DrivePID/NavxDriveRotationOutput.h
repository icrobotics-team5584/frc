#pragma once

#include <WPILib.h>

class NavxDriveRotationOutput : public PIDOutput{
public:
	NavxDriveRotationOutput();
	void PIDWrite(double zRotation);
	virtual ~NavxDriveRotationOutput();
};
