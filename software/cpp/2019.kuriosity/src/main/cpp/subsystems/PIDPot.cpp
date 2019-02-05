

#include "subsystems/PIDPot.h"
#include "Robot.h"

PIDPot::PIDPot() {
	// TODO Auto-generated constructor stub
	_potMain = Robot::_robotMap->subGimblePot;

}

double PIDPot::PIDGet() {

	return _potMain->GetAverageValue();  //this is a analyze error only

}

PIDPot::~PIDPot() {
	// TODO Auto-generated destructor stub
}

