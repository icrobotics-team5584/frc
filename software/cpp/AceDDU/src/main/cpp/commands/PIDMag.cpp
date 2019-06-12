

#include "commands/PIDMag.h"

PIDMag::PIDMag() {
	// TODO Auto-generated constructor stub
	srxArm.reset(new WPI_TalonSRX(3));

}

double PIDMag::PIDGet() {

	return srxArm->GetSelectedSensorPosition(0);
}


PIDMag::~PIDMag() {
	// TODO Auto-generated destructor stub
}

