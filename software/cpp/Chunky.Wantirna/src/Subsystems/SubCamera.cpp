#include "SubCamera.h"
#include "../RobotMap.h"
#include "../Commands/CmdCameraTrack.h"
#include "../Commands/CmdCameraManual.h"
#include "CANTalon.h"

SubCamera::SubCamera() : Subsystem("ExampleSubsystem") {
	//Setup motors
	SpkCameraHorizontal = RobotMap::subCameraHorizontal;
	SpkCameraVirtical = RobotMap::subCameraVirtical;
}

void SubCamera::InitDefaultCommand() {
	//Set Default Command
	SetDefaultCommand(new CmdCameraManual());
}

void SubCamera::Pan(double speed) {
	//Run panning motor at set speed
	SpkCameraHorizontal->Set(-speed/1.5);
}

void SubCamera::Tilt(double speed) {
	//Run tilting motor at set speed
	SpkCameraVirtical->Set(-speed/1.5);
}

void SubCamera::Stop(){
	//Stop both pan and tilt motors
	SpkCameraVirtical->Set(0);
	SpkCameraHorizontal->Set(0);
}

void SubCamera::PublishValues(){
	std::shared_ptr<Joystick> stick = Robot::oi->getJoystick1();
	SmartDashboard::PutNumber("Joystick Camera Axis 2", stick->GetRawAxis(2));
	SmartDashboard::PutNumber("Joystick Camera Axis 5", stick->GetRawAxis(5));
}
