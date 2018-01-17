#ifndef MotionProfileExample__h_
#define MotionProfileExample__h_
/**
 * Example logic for firing and managing motion profiles.
 * This example sends MPs, waits for them to finish
 * Although this code uses a CANTalon, nowhere in this module do we changeMode() or call set() to change the output.
 * This is done in Robot.java to demonstrate how to change control modes on the fly.
 * 
 * The only routines we call on Talon are....
 * 
 * changeMotionControlFramePeriod
 * 
 * getMotionProfileStatus		
 * clearMotionProfileHasUnderrun     to get status and potentially clear the error flag.
 * 
 * pushMotionProfileTrajectory
 * clearMotionProfileTrajectories
 * processMotionProfileBuffer,   to push/clear, and process the trajectory points.
 * 
 * getControlMode, to check if we are in Motion Profile Control mode.
 * 
 * Example of advanced features not demonstrated here...
 * [1] Calling pushMotionProfileTrajectory() continuously while the Talon executes the motion profile, thereby keeping it going indefinitely.
 * [2] Instead of setting the sensor position to zero at the start of each MP, the program could offset the MP's position based on current position. 
 */
#include <Custom/MotionProfileLeftA.h>
#include <Custom/MotionProfileLeftB.h>
#include <Custom/MotionProfileRightA.h>
#include <Custom/MotionProfileRightB.h>
#include <Custom/MotionProfileMidA.h>
#include <Custom/MotionProfileMidB.h>
#include <Custom/MotionProfileRetreatA.h>
#include <Custom/MotionProfileRetreatB.h>
#include <Custom/MotionProfileBaselineA.h>
#include <Custom/MotionProfileBaselineB.h>
#include "Custom/Instrumentation.h"
#include "WPILib.h"
#include "Constants.h"
#include "ctre/phoenix.h"

class MotionProfileExample
{
public:
	/**
	 * The status of the motion profile executer and buffer inside the Talon.
	 * Instead of creating a new one every time we call getMotionProfileStatus,
	 * keep one copy.
	 */
	MotionProfileStatus _statusA;
	MotionProfileStatus _statusB;

	/** additional cache for holding the active trajectory point */
	double _posA=0,_velA=0,_headingA=0;
	double _posB=0,_velB=0,_headingB=0;
	/**
	 * reference to the talon we plan on manipulating. We will not changeMode()
	 * or call set(), just get motion profile status and make decisions based on
	 * motion profile.
	 */
	TalonSRX & _talonMasterA;
	// TalonSRX & _talonSlaveA;
	TalonSRX & _talonMasterB;
	// TalonSRX & _talonSlaveB;
	/**
	 * State machine to make sure we let enough of the motion profile stream to
	 * talon before we fire it.
	 */
	int _state = 0;
	/**
	 * Any time you have a state machine that waits for external events, its a
	 * good idea to add a timeout. Set to -1 to disable. Set to nonzero to count
	 * down to '0' which will print an error message. Counting loops is not a
	 * very accurate method of tracking timeout, but this is just conservative
	 * timeout. Getting time-stamps would certainly work too, this is just
	 * simple (no need to worry about timer overflows).
	 */
	int _loopTimeout = -1;
	/**
	 * If start() gets called, this flag is set and in the control() we will
	 * service it.
	 */
	bool _bStart = false;
	/**
	 * We use this variable to record whether the MP has been started.
	 */
	bool _bStarted = false;

	/**
	 * Since the CANTalon.set() routine is mode specific, deduce what we want
	 * the set value to be and let the calling module apply it whenever we
	 * decide to switch to MP mode.
	 */
	SetValueMotionProfile _setValue = SetValueMotionProfile::Disable;
	/**
	 * How many trajectory points do we wait for before firing the motion
	 * profile.
	 */
	static const int kMinPointsInTalon = 5;
	/**
	 * Just a state timeout to make sure we don't get stuck anywhere. Each loop
	 * is about 20ms.
	 */
	static const int kNumLoopsTimeout = 10;
	/**
	 * Lets create a periodic task to funnel our trajectory points into our
	 * talon. It doesn't need to be very accurate, just needs to keep pace with
	 * the motion profiler executer. Now if you're trajectory points are slow,
	 * there is no need to do this, just call
	 * _talon.processMotionProfileBuffer() in your teleop loop. Generally
	 * speaking you want to call it at least twice as fast as the duration of
	 * your trajectory points. So if they are firing every 20ms, you should call
	 * every 10ms.
	 */
	void PeriodicTask()
	{
		/* keep Talons happy by moving the points from top-buffer to bottom-buffer */
		_talonMasterA.ProcessMotionProfileBuffer();
		_talonMasterB.ProcessMotionProfileBuffer();
	}
	/**
	 * Lets create a periodic task to funnel our trajectory points into our talon.
	 * It doesn't need to be very accurate, just needs to keep pace with the motion
	 * profiler executer.
	 */
	Notifier _notifer;
	int _Profile;

	MotionProfileExample(TalonSRX & talon1, TalonSRX & talon2, int Profile) :
		_talonMasterA(talon1),
		_talonMasterB(talon2),
		_notifer(&MotionProfileExample::PeriodicTask, this),
		_Profile(Profile)
		{
		/*
		 * since our MP is 10ms per point, set the control frame rate and the
		 * notifer to half that
		 */
		_talonMasterA.ChangeMotionControlFramePeriod(5);
		_talonMasterB.ChangeMotionControlFramePeriod(5);

		/* start our tasking */
		_notifer.StartPeriodic(0.005);

	}

	/**
	 * Called to clear Motion profile buffer and reset state info during
	 * disabled and when Talon is not in MP control mode.
	 */
	void reset()
	{
		/*
		 * Let's clear the buffer just in case user decided to disable in the
		 * middle of an MP, and now we have the second half of a profile just
		 * sitting in memory.
		 */
		_talonMasterA.ClearMotionProfileTrajectories();
		_talonMasterB.ClearMotionProfileTrajectories();
		/* When we do re-enter motionProfile control mode, stay disabled. */
		_setValue = SetValueMotionProfile::Disable;
		/* When we do start running our state machine start at the beginning. */
		_state = 0;
		_loopTimeout = -1;
		/*
		 * If application wanted to start an MP before, ignore and wait for next
		 * button press
		 */
		_bStart = false;
	}

	/**
	 * Called every loop.
	 */
	void control()
	{
		/* Get the motion profile status every loop
		 * In some cases we need to access the status of both masters, in others we use MasterA
		 * As the lead and assume MasterB is in sync, this assumption may be unfounded!
		 */
		_talonMasterA.GetMotionProfileStatus(_statusA);
		_talonMasterB.GetMotionProfileStatus(_statusB);

		/*
		 * track time, this is rudimentary but that's okay, we just want to make
		 * sure things never get stuck.
		 */
		if (_loopTimeout < 0) {
			/* do nothing, timeout is disabled */
		} else {
			/* our timeout is nonzero */
			if (_loopTimeout == 0) {
				/*
				 * something is wrong. Talon is not present, unplugged, breaker
				 * tripped
				 */
				instrumentation::OnNoProgress();
			} else {
				--_loopTimeout;
			}
		}

		/* first check if we are in MP mode */
		if(_talonMasterA.GetControlMode() != ControlMode::MotionProfile){
			/*
			 * we are not in MP mode. We are probably driving the robot around
			 * using gamepads or some other mode.
			 */
			_state = 0;
		} else {
			/*
			 * we are in MP control mode. That means: starting Mps, checking Mp
			 * progress, and possibly interrupting MPs if thats what you want to
			 * do.
			 */
			switch (_state) {
				case 0: /* wait for application to tell us to start an MP */
					if (_bStart) {
						_bStart = false;
	
						_setValue = SetValueMotionProfile::Disable;
						startFilling();
						/*
						 * MP is being sent to CAN bus, wait a small amount of time
						 */
						_state = 1;
						_loopTimeout = kNumLoopsTimeout;
					}
					break;
				case 1: /*
						 * wait for MP to stream to Talon, really just the first few
						 * points
						 */
					/* do we have a minimum numberof points in Talon */
					if ((_statusA.btmBufferCnt > kMinPointsInTalon) && (_statusB.btmBufferCnt > kMinPointsInTalon)) {
						/* start (once) the motion profile */
						_setValue = SetValueMotionProfile::Enable;
						/* MP will start once the control frame gets scheduled */
						_state = 2;
						_loopTimeout = kNumLoopsTimeout;
					}
					break;
				case 2: /* check the status of the MP */
					/*
					 * if talon is reporting things are good, keep adding to our
					 * timeout. Really this is so that you can unplug your talon in
					 * the middle of an MP and react to it.
					 */
					if ((_statusA.isUnderrun == false) && (_statusB.isUnderrun == false)){
						_loopTimeout = kNumLoopsTimeout;
					}
					/*
					 * If we are executing an MP and the MP finished, start loading
					 * another. We will go into hold state so robot servo's
					 * position.
					 */
					if (_statusA.activePointValid && _statusA.isLast) {
						/*
						 * because we set the last point's isLast to true, we will
						 * get here when the MP is done
						 */
						_setValue = SetValueMotionProfile::Hold;
						_state = 0;
						_loopTimeout = -1;
					}
					break;
			}
		}

		/* Get the motion profile status every loop */
		_talonMasterA.GetMotionProfileStatus(_statusA);
		_talonMasterB.GetMotionProfileStatus(_statusB);
		_headingA = _talonMasterA.GetActiveTrajectoryHeading();
		_headingB = _talonMasterB.GetActiveTrajectoryHeading();
		_posA = _talonMasterA.GetActiveTrajectoryPosition();
		_posB = _talonMasterB.GetActiveTrajectoryPosition();
		_velA = _talonMasterA.GetActiveTrajectoryVelocity();
		_velB = _talonMasterB.GetActiveTrajectoryVelocity();

		/* printfs and/or logging ... we really need to process statuses better than this as they will appear jumbled in the console when we do it like this  */
		instrumentation::Process(_statusA, _posA, _velA, _headingA);
		instrumentation::Process(_statusB, _posB, _velB, _headingB);
	}
	/**
	 * Find enum value if supported.
	 * @param durationMs
	 * @return enum equivalent of durationMs
	 */
	TrajectoryDuration GetTrajectoryDuration(int durationMs)
	{
		/* lookup and return valid value */
		switch (durationMs) {
			case 0:		return TrajectoryDuration_0ms;
			case 5:		return TrajectoryDuration_5ms;
			case 10: 	return TrajectoryDuration_10ms;
			case 20: 	return TrajectoryDuration_20ms;
			case 30: 	return TrajectoryDuration_30ms;
			case 40: 	return TrajectoryDuration_40ms;
			case 50: 	return TrajectoryDuration_50ms;
			case 100: 	return TrajectoryDuration_100ms;
		}
		printf("Trajectory Duration not supported - use configMotionProfileTrajectoryPeriod instead\n");
		return TrajectoryDuration_100ms;
	}
	/** Start filling the MPs to all of the involved Talons. */
	void startFilling()
	{
		/* since this example only has one talon, just update that one */
		switch (_Profile) {

		//To Left Peg
		case (0):
			startFillingA(kLeftA, kLeftASz);
			startFillingB(kLeftB, kLeftBSz);
			break;

		//To Right Peg
		case (1):
			startFillingA(kRightA, kRightASz);
			startFillingB(kRightB, kRightBSz);
			break;

		//To Mid Peg
		case (2):
			startFillingA(kMidA, kMidASz);
			startFillingB(kMidB, kMidBSz);
			break;

		//To Base Line
		case (3):
			startFillingA(kBaselineA, kBaselineASz);
			startFillingB(kBaselineB, kBaselineBSz);
			break;

		//To Retreat
		case (4):
			startFillingA(kRetreatA, kRetreatASz);
			startFillingB(kRetreatB, kRetreatBSz);
			break;
		}
	}

	void startFillingA(const double profile[][3], int totalCnt)
	{
		/* create an empty point */
		TrajectoryPoint point;

		/* did we get an underrun condition since last time we checked ? */
		if(_statusA.hasUnderrun ){
			/* better log it so we know about it */
			instrumentation::OnUnderrun();
			/*
			 * clear the error. This is what seperates "has underrun" from
			 * "is underrun", because the former is cleared by the application.
			 * That way, we never miss logging it.
			 */
			_talonMasterA.ClearMotionProfileHasUnderrun(Constants::kTimeoutMs);
		}

		/*
		 * just in case we are interrupting another MP and there is still buffer
		 * points in memory, clear it.
		 */
		_talonMasterA.ClearMotionProfileTrajectories();

		/* This is fast since it's just into our TOP buffer */
		for(int i=0;i<totalCnt;++i){
			double positionRot = profile[i][0];
			double velocityRPM = profile[i][1];

			/* for each point, fill our structure and pass it to API */
			point.position = positionRot * Constants::kSensorUnitsPerRotation ;  //Convert Revolutions to Units
			point.velocity = velocityRPM * Constants::kSensorUnitsPerRotation / 600.0; //Convert RPM to Units/100ms
			point.headingDeg = 0; /* future feature - not used in this example*/
			point.profileSlotSelect0 = 0; /* which set of gains would you like to use [0,3]? */
			point.profileSlotSelect1 = 0; /* future feature  - not used in this example - cascaded PID [0,1], leave zero */
			point.timeDur = GetTrajectoryDuration((int)profile[i][2]);
			point.zeroPos = false;
			if (i == 0)
				point.zeroPos = true; /* set this to true on the first point */

			point.isLastPoint = false;
			if ((i + 1) == totalCnt)
				point.isLastPoint = true; /* set this to true on the last point  */
			_talonMasterA.PushMotionProfileTrajectory(point);

			/* For now, lets just reverse the points for the opposite side of drive base */
			point.position *= -1.0;
			point.velocity *= -1.0;
			_talonMasterB.PushMotionProfileTrajectory(point);
		}
	}

	void startFillingB(const double profile[][3], int totalCnt)
	{
		/* create an empty point */
		TrajectoryPoint point;

		/* did we get an underrun condition since last time we checked ? */
		if(_statusB.hasUnderrun ){
			/* better log it so we know about it */
			instrumentation::OnUnderrun();
			/*
			 * clear the error. This is what seperates "has underrun" from
			 * "is underrun", because the former is cleared by the application.
			 * That way, we never miss logging it.
			 */
			_talonMasterB.ClearMotionProfileHasUnderrun(Constants::kTimeoutMs);
		}

		/*
		 * just in case we are interrupting another MP and there is still buffer
		 * points in memory, clear it.
		 */
		_talonMasterB.ClearMotionProfileTrajectories();

		/* This is fast since it's just into our TOP buffer */
		for(int i=0;i<totalCnt;++i){
			double positionRot = profile[i][0];
			double velocityRPM = profile[i][1];

			/* for each point, fill our structure and pass it to API */
			point.position = positionRot * Constants::kSensorUnitsPerRotation ;  //Convert Revolutions to Units
			point.velocity = velocityRPM * Constants::kSensorUnitsPerRotation / 600.0; //Convert RPM to Units/100ms
			point.headingDeg = 0; /* future feature - not used in this example*/
			point.profileSlotSelect0 = 0; /* which set of gains would you like to use [0,3]? */
			point.profileSlotSelect1 = 0; /* future feature  - not used in this example - cascaded PID [0,1], leave zero */
			point.timeDur = GetTrajectoryDuration((int)profile[i][2]);
			point.zeroPos = false;
			if (i == 0)
				point.zeroPos = true; /* set this to true on the first point */

			point.isLastPoint = false;
			if ((i + 1) == totalCnt)
				point.isLastPoint = true; /* set this to true on the last point  */

			_talonMasterB.PushMotionProfileTrajectory(point);
		}
	}
	
	/**
	 * Called by application to signal Talon to start the buffered MP (when it's
	 * able to).
	 */
	void start() {
		_bStart = true;
		_bStarted = true;
	}

	/**
	 * Called by command object to establish whether MP is running.
	 */
	int getState() {
		return _state;
	}

	/**
	 * Called by command object to establish whether MP has been started.
	 */
	bool hasBeenStarted() {
		return _bStarted;
	}

	/**
	 * 
	 * @return the output value to pass to Talon's set() routine. 0 for disable
	 *         motion-profile output, 1 for enable motion-profile, 2 for hold
	 *         current motion profile trajectory point.
	 */
	SetValueMotionProfile getSetValue() {
		return _setValue;
	}
};
#endif // MotionProfileExample__h_
