#ifndef SubCamera_H
#define SubCamera_H
#include "NetworkTables/NetworkTable.h"
#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "ctre/phoenix.h"

class SubCamera : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<SpeedController> SpkCameraHorizontal;
	std::shared_ptr<SpeedController> SpkCameraVirtical;

public:
	SubCamera();
	void InitDefaultCommand();
	void Pan(double);
	void Tilt(double);
	void Stop();
	void PublishValues();
};

#endif  // SubCamera_H
