

#include "commands/PIDMag.h"

PIDMag::PIDMag() {
	// TODO Auto-generated constructor stub
	srxArm.reset(new WPI_TalonSRX(3));

}

double PIDMag::PIDGet() {

	return srxArm->GetSelectedSensorPosition(0);
}


PIDPot::~PIDMag() {
	// TODO Auto-generated destructor stub
}

