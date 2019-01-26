/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubElevator.h"
#include "Robot.h"

SubElevator::SubElevator() : Subsystem("ExampleSubsystem") {
  _srxElevator = Robot::_robotMap->srxElevator;
  _subElevatorLimitBottom = Robot::_robotMap->subElevatorLimitBottom;
  _subElevatorLimitTop = Robot::_robotMap->subElevatorLimitTop;
   enum Constants
    {
    	/**
    	 * Which PID slot to pull gains from.  Starting 2018, you can choose
    	 * from 0,1,2 or 3.  Only the first two (0,1) are visible in web-based configuration.
    	 */
    	 kSlotIdx = 0,

    	/* Talon SRX/ Victor SPX will supported multiple (cascaded) PID loops.
    	 * For now we just want the primary one.
    	 */
    	 kPIDLoopIdx = 0,

    	/*
    	 * set to zero to skip waiting for confirmation, set to nonzero to wait
    	 * and report to DS if action fails.
    	 */
    	 kTimeoutMs = 10
    };

	/* lets grab the 360 degree position of the MagEncoder's absolute position */
	int absolutePosition = _srxElevator->GetSelectedSensorPosition(0) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
		/* use the low level API to set the quad encoder signal */
	_srxElevator->SetSelectedSensorPosition(absolutePosition, kPIDLoopIdx, kTimeoutMs);

	/* choose the sensor and sensor direction */
	_srxElevator->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, kPIDLoopIdx, kTimeoutMs);
	_srxElevator->SetSensorPhase(false);

	/* set the peak and nominal outputs, 12V means full */
	_srxElevator->ConfigNominalOutputForward(0, kTimeoutMs);
	_srxElevator->ConfigNominalOutputReverse(0, kTimeoutMs);
	_srxElevator->ConfigPeakOutputForward(0.1, kTimeoutMs);
	_srxElevator->ConfigPeakOutputReverse(-0.1, kTimeoutMs);

  /* set closed loop gains in slot0 */
	_srxElevator->Config_kF(kPIDLoopIdx, 0.0, kTimeoutMs);
	_srxElevator->Config_kP(kPIDLoopIdx, 2.0, kTimeoutMs);
	_srxElevator->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
	_srxElevator->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);

}

void SubElevator::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void SubElevator::ElevatorToPos(double rotation) {
  targetPosRotations = -(rotation * 4096);
  _srxElevator->Set(ControlMode::Position, targetPosRotations);
}

void SubElevator::Override(std::shared_ptr<Joystick> rightStick){
	_axis5 = rightStick->GetRawAxis(5); //up down control axis  

	if (_axis5 > 0.5) { //down
		targetPositionRotations = targetPositionRotations + overrideSpeed;
	} else if (_axis5 <-0.5){ //up
		targetPositionRotations = targetPositionRotations - overrideSpeed;
	}

	_srxElevator->Set(ControlMode::Position, targetPositionRotations);
}

void SubElevator::Stop() {
	targetPositionRotations = (_srxElevator->GetSelectedSensorPosition(0));
	_srxElevator->Set(ControlMode::Position, targetPositionRotations);
}