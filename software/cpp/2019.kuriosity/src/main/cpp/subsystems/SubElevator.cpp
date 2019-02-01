#include "subsystems/SubElevator.h"
#include "Robot.h"

SubElevator::SubElevator() : Subsystem("ExampleSubsystem") {
  _srxElevatorMaster = Robot::_robotMap->srxElevatorMaster;
  
//   enum Constants
//    {
//    	/**
//    	 * Which PID slot to pull gains from.  Starting 2018, you can choose
//    	 * from 0,1,2 or 3.  Only the first two (0,1) are visible in web-based configuration.
//    	 */
//    	 kSlotIdx = 0,
//
//    	/* Talon SRX/ Victor SPX will supported multiple (cascaded) PID loops.
//    	 * For now we just want the primary one.
//    	 */
//    	 kPIDLoopIdx = 0,
//
//    	/*
//    	 * set to zero to skip waiting for confirmation, set to nonzero to wait
//    	 * and report to DS if action fails.
//    	 */
//    	 kTimeoutMs = 10
//    };
//
//	/* lets grab the 360 degree position of the MagEncoder's absolute position */
//	int absolutePosition = _srxElevatorMaster->GetSelectedSensorPosition(0) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
//		/* use the low level API to set the quad encoder signal */
//	_srxElevatorMaster->SetSelectedSensorPosition(absolutePosition, kPIDLoopIdx, kTimeoutMs);
//
//	/* choose the sensor and sensor direction */
//	_srxElevatorMaster->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, kPIDLoopIdx, kTimeoutMs);
//	_srxElevatorMaster->SetSensorPhase(false);
//
//	/* set the peak and nominal outputs, 12V means full */
//	_srxElevatorMaster->ConfigNominalOutputForward(0, kTimeoutMs);
//	_srxElevatorMaster->ConfigNominalOutputReverse(0, kTimeoutMs);
//	_srxElevatorMaster->ConfigPeakOutputForward(0.1, kTimeoutMs);
//	_srxElevatorMaster->ConfigPeakOutputReverse(-0.1, kTimeoutMs);
//
//  /* set closed loop gains in slot0 */
//	_srxElevatorMaster->Config_kF(kPIDLoopIdx, 0.0, kTimeoutMs);
//	_srxElevatorMaster->Config_kP(kPIDLoopIdx, 2.0, kTimeoutMs);
//	_srxElevatorMaster->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
//	_srxElevatorMaster->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);

}

void SubElevator::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void SubElevator::ElevatorToPos(double rotation) {
  targetPosRotations = -(rotation * 4096);
  _srxElevatorMaster->Set(ControlMode::Position, targetPosRotations);
}

void SubElevator::Override(std::shared_ptr<Joystick> rightStick){
	_axis5 = rightStick->GetRawAxis(5); //up down control axis  

	if (_axis5 > 0.5) { //down
		targetPositionRotations = targetPositionRotations + overrideSpeed;
	} else if (_axis5 <-0.5){ //up
		targetPositionRotations = targetPositionRotations - overrideSpeed;
	}

	_srxElevatorMaster->Set(ControlMode::Position, targetPositionRotations);
}

void SubElevator::Stop() {
	targetPositionRotations = (_srxElevatorMaster->GetSelectedSensorPosition(0));
	_srxElevatorMaster->Set(ControlMode::Position, targetPositionRotations);
}
void SubElevator::TestingUp() {
	SmartDashboard::PutNumber("Elevator Up Speed", elevatorUpSpeed);
	_srxElevatorMaster->Set(elevatorUpSpeed);
}
void SubElevator::TestingDown() {
	SmartDashboard::PutNumber("Elevator Down Speed", elevatorDownSpeed);
	_srxElevatorMaster->Set(elevatorDownSpeed);
}
void SubElevator::TestingStop() {
	_srxElevatorMaster->Set(0.0);
}


