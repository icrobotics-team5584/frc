#include "subsystems/SubElevator.h"
#include "Robot.h"

SubElevator::SubElevator() : Subsystem("ExampleSubsystem") {
	
  _srxElevatorMaster = Robot::_robotMap->srxElevatorMaster;
  SmartDashboard::PutNumber("Elevator PIDP", PIDP);
  SmartDashboard::PutNumber("Elevator PIDI", PIDI);
  SmartDashboard::PutNumber("Elevator PIDD", PIDD);
  SmartDashboard::PutNumber("Elevator PID target", targetPositionRotations);

	/* lets grab the 360 degree position of the MagEncoder's absolute position */
	int absolutePosition = _srxElevatorMaster->GetSelectedSensorPosition(0) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
		/* use the low level API to set the quad encoder signal */
	_srxElevatorMaster->SetSelectedSensorPosition(0.0, kPIDLoopIdx, kTimeoutMs);

	/* choose the sensor and sensor direction */
	_srxElevatorMaster->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, kPIDLoopIdx, kTimeoutMs);	_srxElevatorMaster->SetSensorPhase(false);

	/* set the peak and nominal outputs, 12V means full */
	_srxElevatorMaster->ConfigNominalOutputForward(0, kTimeoutMs);
	_srxElevatorMaster->ConfigNominalOutputReverse(0, kTimeoutMs);
	_srxElevatorMaster->ConfigPeakOutputForward(0.4, kTimeoutMs);
	_srxElevatorMaster->ConfigPeakOutputReverse(-0.8, kTimeoutMs);

  /* set closed loop gains in slot0 */
	_srxElevatorMaster->Config_kF(kPIDLoopIdx, 0.0, kTimeoutMs);
	_srxElevatorMaster->Config_kP(kPIDLoopIdx, PIDP, kTimeoutMs);
	_srxElevatorMaster->Config_kI(kPIDLoopIdx, PIDI, kTimeoutMs);
	_srxElevatorMaster->Config_kD(kPIDLoopIdx, PIDD, kTimeoutMs);
}

void SubElevator::Periodic() {
	SmartDashboard::PutNumber("ELEVATOR", _srxElevatorMaster->GetSelectedSensorPosition(0));
	//PIDP = SmartDashboard::GetNumber("Elevator PIDP", 0.0);
	PIDI = SmartDashboard::GetNumber("Elevator PIDI", 0.0);
	PIDD = SmartDashboard::GetNumber("Elevator PIDD", 0.0);
	//targetPositionRotations = SmartDashboard::GetNumber("Elevator PID target", 0.0);

	_srxElevatorMaster->Config_kF(kPIDLoopIdx, 0.0, kTimeoutMs);
	_srxElevatorMaster->Config_kP(kPIDLoopIdx, PIDP, kTimeoutMs);
	_srxElevatorMaster->Config_kI(kPIDLoopIdx, PIDI, kTimeoutMs);
	_srxElevatorMaster->Config_kD(kPIDLoopIdx, PIDD, kTimeoutMs);
}

void SubElevator::InitDefaultCommand() {
// Set the default command for a subsystem here.
// SetDefaultCommand(new MySpecialCommand());

 //Put methods for controlling this subsystem
 //here. Call these from Commands.
}

void SubElevator::ElevatorToPos(double rotation) {
  targetPositionRotations = (rotation * -4096);
  _srxElevatorMaster->Set(ControlMode::Position, targetPositionRotations);
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

void SubElevator::PIDEnable() {
	cout << "Elevator PID go" << endl;

}
void SubElevator::PIDDisable() {
	cout << "Elevator PID stop" << endl;
	_srxElevatorMaster->Set(ControlMode::PercentOutput, 0.0);
}

void SubElevator::Stop() {
	cout << "ELEVATOR stop" << endl;
	targetPositionRotations = (_srxElevatorMaster->GetSelectedSensorPosition(0));
	_srxElevatorMaster->Set(ControlMode::Position, targetPositionRotations);
}

void SubElevator::TestingUp() {
	_srxElevatorMaster->Set(-0.6);
}


void SubElevator::TestingDown() {
	_srxElevatorMaster->Set(0.2);
}

void SubElevator::TestingStop() {
	_srxElevatorMaster->Set(0.0);
}

void SubElevator::TestingUpStop() {
	_srxElevatorMaster->Set(-0.1);
}

int SubElevator::GetEncoderPosition() {
	return _srxElevatorMaster->GetSelectedSensorPosition(0);
}

void SubElevator::EncoderReset() {
	_srxElevatorMaster->SetSelectedSensorPosition(0, 0, 10);
	targetPositionRotations = 0;
	_srxElevatorMaster->Set(ControlMode::Position, targetPositionRotations);
}

void SubElevator::TestingPID() {
	cout << "ELEVATOR PID" << endl;
	_srxElevatorMaster->Set(ControlMode::Position, (targetPositionRotations * -4096));
	cout << "Sub Elevater PID target" << targetPositionRotations << endl;
}



