#ifndef SRC_MOTIONPROFILECONTROL_H_
#define SRC_MOTIONPROFILECONTROL_H_

#include <ctre/Phoenix.h>
#include <WPILib.h>
#include <iostream>
#include "MotionProfileData.h"

using namespace ctre::phoenix::motion;

class MotionProfileControl {
public:
	MotionProfileControl(	std::shared_ptr<TalonSRX>,
							std::shared_ptr<TalonSRX>,
							std::shared_ptr<MotionProfileData>);
	SetValueMotionProfile GetSetValue();
	void control();
	void startFilling();
	void start();
	void stop();
	void execute();
	void initialise();

private:
	MotionProfileStatus _statusA;
	MotionProfileStatus _statusB;

	double _posA=0,_velA=0,_headingA=0;
	double _posB=0,_velB=0,_headingB=0;

	SetValueMotionProfile _setValue;
	std::shared_ptr<TalonSRX> _leftTalon;
	std::shared_ptr<TalonSRX> _rightTalon;
	std::shared_ptr<MotionProfileData> _mp;
	Notifier _notifier;

	bool _bStart;
	int _state;
	int _loopTimeout;
	int _loopCount;

	const int kMinPointsInTalon = 5;
	const int kNumLoopsTimeout = 10;
	const int kTimeoutMs = 10;
	const int kTopBufferSize = 4000;
	const double kSensorUnitsPerRotation = 4096;

	enum Pos {first, mid, last};
	void PushToTalon(TrajectoryPoint, std::shared_ptr<TalonSRX>, int side);
	void PeriodicTask();
	void reset();

	bool firsttimearound = true;
	int execounter = 0;

};

#endif /* SRC_MOTIONPROFILECONTROL_H_ */
