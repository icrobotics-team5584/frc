#include "SubEncodedArmLift.h"
#include "../RobotMap.h"

SubEncodedArmLift::SubEncodedArmLift() : Subsystem("ExampleSubsystem") {

	_talon = RobotMap::subEncodedArmLiftSrxMaster;
	_prefs = Preferences::GetInstance();

	/* lets grab the 360 degree position of the MagEncoder's absolute position */
	absolutePosition = _talon->GetSelectedSensorPosition(0) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
	/* use the low level API to set the quad encoder signal */
	_talon->SetSelectedSensorPosition(absolutePosition, kPIDLoopIdx, kTimeoutMs);

	/* choose the sensor and sensor direction */
	_talon->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, kPIDLoopIdx, kTimeoutMs);
	_talon->SetSensorPhase(true);

	/* set the peak and nominal outputs, 12V means full */
	_talon->ConfigNominalOutputForward(0, kTimeoutMs);
	_talon->ConfigNominalOutputReverse(0, kTimeoutMs);
	_talon->ConfigPeakOutputForward(1, kTimeoutMs);
	_talon->ConfigPeakOutputReverse(-1, kTimeoutMs);

	/* set closed loop gains in slot0 */
	_talon->Config_kF(kPIDLoopIdx, 0.0, kTimeoutMs);
	_talon->Config_kP(kPIDLoopIdx, 0.1, kTimeoutMs);
	_talon->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
	_talon->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);

}

void SubEncodedArmLift::ArmToGroundPos() {

	_groundTarget = _prefs->GetDouble("Ground Position", 0.0);
	targetPositionRotations = _groundTarget;
	_talon->Set(ControlMode::Position, targetPositionRotations);

	/* if Talon is in position closed-loop, print some more info */
		if (_talon->GetControlMode() == ControlMode::Position) {
			/* append more signals to print when in speed mode. */
			_sb.append("\terrNative:");
			_sb.append(std::to_string(_talon->GetClosedLoopError(kPIDLoopIdx)));
			_sb.append("\ttrg:");
			_sb.append(std::to_string(targetPositionRotations));
		}
		/* print every ten loops, printing too much too fast is generally bad for performance */
		if (++_loops >= 10) {
			_loops = 0;
			//printf("%s\n",_sb.c_str());
			frc::SmartDashboard::PutString("EncodedArmLift", _sb);
		}
		_sb.clear();

}

void SubEncodedArmLift::ArmToSwitchPos() {

	_switchTarget = _prefs->GetDouble("Switch Position", 0.0);
	targetPositionRotations = _switchTarget;
	_talon->Set(ControlMode::Position, targetPositionRotations);

	/* if Talon is in position closed-loop, print some more info */
		if (_talon->GetControlMode() == ControlMode::Position) {
			/* append more signals to print when in speed mode. */
			_sb.append("\terrNative:");
			_sb.append(std::to_string(_talon->GetClosedLoopError(kPIDLoopIdx)));
			_sb.append("\ttrg:");
			_sb.append(std::to_string(targetPositionRotations));
		}
		/* print every ten loops, printing too much too fast is generally bad for performance */
		if (++_loops >= 10) {
			_loops = 0;
			//printf("%s\n",_sb.c_str());
			frc::SmartDashboard::PutString("EncodedArmLift", _sb);
		}
		_sb.clear();

}

void SubEncodedArmLift::ArmToScalePos() {

	_scaleTarget = _prefs->GetDouble("Scale Position", 0.0);
	targetPositionRotations = _scaleTarget;
	_talon->Set(ControlMode::Position, targetPositionRotations);

	/* if Talon is in position closed-loop, print some more info */
		if (_talon->GetControlMode() == ControlMode::Position) {
			/* append more signals to print when in speed mode. */
			_sb.append("\terrNative:");
			_sb.append(std::to_string(_talon->GetClosedLoopError(kPIDLoopIdx)));
			_sb.append("\ttrg:");
			_sb.append(std::to_string(targetPositionRotations));
		}
		/* print every ten loops, printing too much too fast is generally bad for performance */
		if (++_loops >= 10) {
			_loops = 0;
			//printf("%s\n",_sb.c_str());
			frc::SmartDashboard::PutString("EncodedArmLift", _sb);
		}
		_sb.clear();

}

void SubEncodedArmLift::Periodic() {

//	/* get gamepad axis */
//		leftYstick = _joy->GetY();
//		motorOutput = _talon->GetMotorOutputPercent();
//		button1 = _joy->GetRawButton(11);
//		button2 = _joy->GetRawButton(12);
//
//
//		/* prepare line to print */
//				_sb.append("\tout:");
//				_sb.append(std::to_string(motorOutput));
//				_sb.append("\tpos:");
//				_sb.append(std::to_string(_talon->GetSelectedSensorPosition(kPIDLoopIdx)));
//				/* on button1 press enter closed-loop mode on target position */
//				if (!_lastButton1 && button1) {
//					/* Position mode - button just pressed */
//					targetPositionRotations = leftYstick * 10.0 * 4096; /* 50 Rotations in either direction */
//					_talon->Set(ControlMode::Position, targetPositionRotations); /* 50 rotations in either direction */
//
//				}
//				/* on button2 just straight drive */
//				if (button2) {
//					/* Percent voltage mode */
//					_talon->Set(ControlMode::PercentOutput, leftYstick);
//				}
//				/* if Talon is in position closed-loop, print some more info */
//				if (_talon->GetControlMode() == ControlMode::Position) {
//					/* append more signals to print when in speed mode. */
//					_sb.append("\terrNative:");
//					_sb.append(std::to_string(_talon->GetClosedLoopError(kPIDLoopIdx)));
//					_sb.append("\ttrg:");
//					_sb.append(std::to_string(targetPositionRotations));
//				}
//				/* print every ten loops, printing too much too fast is generally bad for performance */
//				if (++_loops >= 10) {
//					_loops = 0;
//					printf("%s\n",_sb.c_str());
//				}
//				_sb.clear();
//				/* save button state for on press detect */
//				_lastButton1 = button1;

}


void SubEncodedArmLift::TakeJoystickInputs(std::shared_ptr<Joystick> _joyTemp ) {

	_joy = _joyTemp;

}

void SubEncodedArmLift::InitDefaultCommand() {




}

// Put methods for controlling this subsystem
// here. Call these from Commands.
