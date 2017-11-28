#include "SubCamera.h"
#include "../RobotMap.h"
#include "../Commands/CmdCameraTrack.h"
#include "CANTalon.h"

SubCamera::SubCamera() : Subsystem("ExampleSubsystem") {
	//Setup motors
	SpkCameraHorizontal = RobotMap::subCameraHorizontal;
	SpkCameraVirtical = RobotMap::subCameraVirtical;
}

void SubCamera::InitDefaultCommand() {
	//Set Default Command
	SetDefaultCommand(new CmdCameraTrack());
}

void SubCamera::Pan(double speed) {
	//Run panning motor at set speed
	SpkCameraHorizontal->Set(speed);
}

void SubCamera::Tilt(double speed) {
	//Run tilting motor at set speed
	SpkCameraVirtical->Set(speed);
}

void SubCamera::Stop(){
	//Stop both pan and tilt motors
	SpkCameraVirtical->Set(0);
	SpkCameraHorizontal->Set(0);
}
