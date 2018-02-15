#include <NavxDriveRotationOutput.h>
#include "Robot.h"

NavxDriveRotationOutput::NavxDriveRotationOutput() {
	// TODO Auto-generated constructor stub

}

void NavxDriveRotationOutput::PIDWrite(double output){
	//Called periodically by the turnController
	Robot::subDriveBase->SetPIDRotation(output);
}

NavxDriveRotationOutput::~NavxDriveRotationOutput() {
	// TODO Auto-generated destructor stub
}

