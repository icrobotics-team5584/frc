#include "NavxDriveSpeedOutput.h"
#include "Robot.h"

NavxDriveSpeedOutput::NavxDriveSpeedOutput() {
	// TODO Auto-generated constructor stub

}

void NavxDriveSpeedOutput::PIDWrite(double output){
	//Called periodically by the driveController
	Robot::subDriveBase->SetPIDSpeed(output);
}

NavxDriveSpeedOutput::~NavxDriveSpeedOutput() {
	// TODO Auto-generated destructor stub
}

