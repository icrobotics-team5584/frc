#pragma once

#include <WPILib.h>

class EncoderDistanceSource : public PIDSource{
public:
	EncoderDistanceSource();
	double PIDGet();
	virtual ~EncoderDistanceSource();
};
