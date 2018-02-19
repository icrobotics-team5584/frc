#include "SubCameras.h"
#include "../RobotMap.h"
#include <CameraServer.h>

SubCameras::SubCameras() : Subsystem("ExampleSubsystem") {

	_cameraA = CameraServer::GetInstance()->StartAutomaticCapture(0);
	_cameraA.SetResolution(320, 240);
	_cameraA.SetFPS(10);

	_cameraB = CameraServer::GetInstance()->StartAutomaticCapture(1);
	_cameraB.SetResolution(320, 240);
	_cameraB.SetFPS(10);

	_prevTrigger = 0;
	server = CameraServer::GetInstance()->GetServer();

}


void SubCameras::Periodic() {

}

void SubCameras::ChangeCamera() {

	if ( _prevTrigger == 0) {
	 printf("Setting camera B\n");;
		server.SetSource(_cameraB);
		_prevTrigger = 1;
	} else   {
		printf("Setting camera A\n");
		server.SetSource(_cameraA);
		_prevTrigger = 1;
  }


}

//void SubCameras::TakeJoystickInputs(std::shared_ptr<Joystick> camJoy ) {
//
//	_camJoy = camJoy;
//}

void SubCameras::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
