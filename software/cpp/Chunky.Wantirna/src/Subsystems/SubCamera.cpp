#include "SubCamera.h"
#include "../RobotMap.h"
#include "../Commands/CmdCameraTrack.h"
#include "CANTalon.h"

SubCamera::SubCamera() : Subsystem("ExampleSubsystem") {
	//Setup motors
	TnxCameraHorizontal = RobotMap::subCameraHorizontal;
	TnxCameraVirtical = RobotMap::subCameraVirtical;
}

void SubCamera::InitDefaultCommand() {
	//Set Default Command
	SetDefaultCommand(new CmdCameraTrack());
}

void SubCamera::Pan(double speed) {
	//Run panning motor at set speed
	TnxCameraHorizontal->Set(speed);
}

void SubCamera::Tilt(double speed) {
	//Run tilting motor at set speed
	TnxCameraVirtical->Set(speed);
}

void SubCamera::Stop(){
	//Stop both pan and tilt motors
	TnxCameraVirtical->Set(0);
	TnxCameraHorizontal->Set(0);
}
