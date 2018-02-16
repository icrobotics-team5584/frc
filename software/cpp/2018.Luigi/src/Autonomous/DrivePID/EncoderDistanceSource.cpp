#include "EncoderDistanceSource.h"
#include "Robot.h"

EncoderDistanceSource::EncoderDistanceSource() {
	// TODO Auto-generated constructor stub

}

double EncoderDistanceSource::PIDGet(){
	//Implementation of PIDSource
	return Robot::subDriveBase->GetEncoderDistance();
}

EncoderDistanceSource::~EncoderDistanceSource() {
	// TODO Auto-generated destructor stub
}

