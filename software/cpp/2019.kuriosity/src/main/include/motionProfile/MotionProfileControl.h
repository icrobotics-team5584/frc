#ifndef SRC_MOTIONPROFILECONTROL_H_
#define SRC_MOTIONPROFILECONTROL_H_

#include <ctre/Phoenix.h>
#include <frc/WPILib.h>
#include <iostream>
#include "MotionProfileData.h"

using namespace frc;
using namespace ctre::phoenix::motion;

class MotionProfileControl {
public:
	// Create a MP that automatically reads data in from a csv
	MotionProfileControl(	std::shared_ptr<TalonSRX>,
							std::shared_ptr<TalonSRX>,
							std::string profile,
							int timeout);

	// Cretate a MP with a manually created MotionProfileData object
	MotionProfileControl(	std::shared_ptr<TalonSRX>,
							std::shared_ptr<TalonSRX>,
							std::shared_ptr<MotionProfileData> mpData,
							int timeout);

	SetValueMotionProfile GetSetValue();
	void control();
	void streamToTopBuffer( bool );
	void start();
	void stop();
	void execute();
	void initialise();
	void load();
	bool IsRunning();

private:

	std::string _profile;

	MotionProfileStatus _statusA;
	MotionProfileStatus _statusB;

	std::shared_ptr<MotionProfileData> _mpData;

	double _posA=0,_velA=0,_headingA=0;
	double _posB=0,_velB=0,_headingB=0;

	SetValueMotionProfile _setValue;
	std::shared_ptr<TalonSRX> _leftTalon;
	std::shared_ptr<TalonSRX> _rightTalon;
	Notifier _notifier;

	bool _bStart;
	int _state;
	int _loopTimeout;
	int _loopCount;
	int _pointsprocessed;
	int _profileTimeout;

	const int kMinPointsInTalon = 5;
	const int kNumLoopsTimeout = 10;
	const int kTimeoutMs = 10;
	const int kTopBufferSize = 4000;
	const int kBlockSize = 128;
	const double kSensorUnitsPerRotation = 4096;

	enum Pos {first, mid, last};
	void PushToTalon(TrajectoryPoint, std::shared_ptr<TalonSRX>, int side);
	void PeriodicTask();
	void reset();

	bool firsttimearound = true;
	int execounter = 0;
	bool isRunning;

};

#endif /* SRC_MOTIONPROFILECONTROL_H_ */
