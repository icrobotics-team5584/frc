#ifndef SRC_MOTIONPROFILECONTROL_H_
#define SRC_MOTIONPROFILECONTROL_H_

#include <ctre/Phoenix.h>
#include <WPILib.h>
#include <iostream>

using namespace ctre::phoenix::motion;

class MotionProfileControl {
public:
	MotionProfileControl(	std::shared_ptr<TalonSRX>,
							std::shared_ptr<TalonSRX>,
							const double *,
							const double *,
							const int);
	SetValueMotionProfile GetSetValue();
	void control();
	void startFilling(double *, double *, int);
	void start();
	void stop();

private:
	MotionProfileStatus _status;
	SetValueMotionProfile _setValue;
	std::shared_ptr<TalonSRX> _leftTalon;
	std::shared_ptr<TalonSRX> _rightTalon;
	std::shared_ptr<TalonSRX> _talons[2] = {_leftTalon, _rightTalon};
	Notifier _notifier;

	double * _leftMP;
	double * _rightMP;
	double arrL[][3];
	double arrR[][3];

	bool _bStart;
	int _state;
	int _loopTimeout;
	int _loopCount;
	int _arrLength;

	const int kMinPointsInTalon = 5;
	const int kNumLoopsTimeout = 10;
	const int kTimeoutMs = 10;
	const double kSensorUnitsPerRotation = 4096;

	enum Pos {first, mid, last};
	void PushToTalon(double[3], std::shared_ptr<TalonSRX>, Pos);
	void PeriodicTask();
	void reset();
};

#endif /* SRC_MOTIONPROFILECONTROL_H_ */
