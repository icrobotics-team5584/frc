#ifndef SubCameras_H
#define SubCameras_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <cscore_oo.h>

class SubCameras : public Subsystem {
private:

	int _prevTrigger;
	//std::shared_ptr<frc::Joystick> _camJoy;
	cs::VideoSink server;
	cs::UsbCamera _cameraA;
	cs::UsbCamera _cameraB;

public:
	SubCameras();
	void InitDefaultCommand();
	void Periodic();
	void ChangeCamera();
	void TakeJoystickInputs(std::shared_ptr<Joystick>);
};

#endif  // SubCameras_H
