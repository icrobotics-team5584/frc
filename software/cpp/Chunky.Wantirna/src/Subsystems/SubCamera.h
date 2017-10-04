#ifndef SubCamera_H
#define SubCamera_H
#include "NetworkTables/NetworkTable.h"
#include <Commands/Subsystem.h>
#include "WPILib.h"

class SubCamera : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<CANTalon> TnxCameraHorizontal;
	std::shared_ptr<CANTalon> TnxCameraVirtical;

public:
	SubCamera();
	void InitDefaultCommand();
	void Pan(double);
	void Tilt(double);
	void Stop();
};

#endif  // SubCamera_H
