#include "SubEncodedArmLift.h"
#include "../RobotMap.h"

#include <WPILib.h>
#include <ctre/Phoenix.h>
#include "Constants.h"

SubEncodedArmLift::SubEncodedArmLift() : Subsystem("ExampleSubsystem") {

	TWO = 1;
	THREE = 1;
	FOUR = 1;

	_talon = RobotMap::subEncodedArmLiftSrxMaster;
	_prefs = Preferences::GetInstance();

	targetPositionRotations = 0.0;

	/* lets grab the 360 degree position of the MagEncoder's absolute position */
	absolutePosition = _talon->GetSelectedSensorPosition(0) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
		/* use the low level API to set the quad encoder signal */
	_talon->SetSelectedSensorPosition(absolutePosition, kPIDLoopIdx, kTimeoutMs);

	/* choose the sensor and sensor direction */
	_talon->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, kPIDLoopIdx, kTimeoutMs);
	_talon->SetSensorPhase(false);

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

void SubEncodedArmLift::ArmToGroundPos() {  //Button 10

	frc::SmartDashboard::PutNumber("Ground", TWO);
    TWO++;

	//targetPositionRotations = (_prefs->GetDouble("Ground Position", 0.0))*4096;
	targetPositionRotations = 0.0;
	_talon->Set(ControlMode::Position, targetPositionRotations);


}

void SubEncodedArmLift::ArmToSwitchPos() {  //Button 11

	frc::SmartDashboard::PutNumber("Switch", THREE);
	THREE++;


	//targetPositionRotations = (_prefs->GetDouble("Switch Position", 0.0))*4096;
	targetPositionRotations = 0.0;
	_talon->Set(ControlMode::Position, targetPositionRotations);



}

void SubEncodedArmLift::ArmToScalePos() {  //Button 12

	frc::SmartDashboard::PutNumber("Scale", FOUR);
    FOUR++;

	//targetPositionRotations = (_prefs->GetDouble("Scale Position", 0.0))*4096;
	targetPositionRotations = 2.0 * 4096;
	_talon->Set(ControlMode::Position, targetPositionRotations);



}

void SubEncodedArmLift::Periodic() {

//	frc::SmartDashboard::PutNumber("_talon current /start position", 555);
	absolutePosition = _talon->GetSelectedSensorPosition(0) & 0xFFF;
	if (++_loops >= 40) {
		frc::SmartDashboard::PutNumber("_talon current /start position", absolutePosition);
		_loops = 0;
	}


}




void SubEncodedArmLift::InitDefaultCommand() {


}

// Put methods for controlling this subsystem
// here. Call these from Commands.
