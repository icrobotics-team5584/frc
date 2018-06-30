

#include "PIDPot.h"
#include "../RobotMap.h"

PIDPot::PIDPot() {
	// TODO Auto-generated constructor stub
	_potMain = RobotMap::subEncodedArmPot;

}

double PIDPot::PIDGet() {

	return _potMain->GetAverageValue();  //this is a analyze error only

}

PIDPot::~PIDPot() {
	// TODO Auto-generated destructor stub
}

