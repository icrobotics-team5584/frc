

#include "PIDPot.h"

PIDPot::PIDPot() {
	// TODO Auto-generated constructor stub
	_potMain = RobotMap::subEncodedArmPot;

}

double PIDPot::PIDGet() {

	return _potMain->GetAverageValue();

}

PIDPot::~PIDPot() {
	// TODO Auto-generated destructor stub
}

