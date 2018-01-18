#ifndef SRC_MOTIONPROFILECONTROL_H_
#define SRC_MOTIONPROFILECONTROL_H_

#include <ctre/Phoenix.h>
#include <WPILib.h>
#include <iostream>

using namespace ctre::phoenix::motion;

class MotionProfileControl {
public:
	MotionProfileControl(std::shared_ptr<TalonSRX>, std::shared_ptr<TalonSRX>, double[][3], double[][3], int);
	SetValueMotionProfile GetSetValue();
	void control();
	void startFilling(double[][3], double[][3], int);
	void start();

private:
	MotionProfileStatus _status;
	SetValueMotionProfile _setValue;
	std::shared_ptr<TalonSRX> _leftTalon;
	std::shared_ptr<TalonSRX> _rightTalon;
	std::shared_ptr<TalonSRX> _talons[2] = {_leftTalon, _rightTalon};
	Notifier _notifier;

	double _leftMP[][3];
	double _rightMP[][3];

	bool _bStart;
	int _state;
	int _loopTimeout;

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
