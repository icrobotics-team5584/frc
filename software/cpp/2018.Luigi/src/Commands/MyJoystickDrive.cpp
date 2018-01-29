#include "MyJoystickDrive.h"

MyJoystickDrive::MyJoystickDrive(): frc::Command() {
    //requires(Robot::chassis.get());
	Requires(Robot::subDriveBase.get());
	Requires(Robot::subEncodedArmLift.get());
}

// Called just before this Command runs the first time
void MyJoystickDrive::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void MyJoystickDrive::Execute() {
    Robot::subDriveBase->TakeJoystickInputs(Robot::oi->getJoystick0());
    Robot::subEncodedArmLift->TakeJoystickInputs(Robot::oi->getJoystick0());
}

// Make this return true when this Command no longer needs to run execute()
bool MyJoystickDrive::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void MyJoystickDrive::End() {

}

// Called when another command which requires one or more of the same subsystems is scheduled to run
void MyJoystickDrive::Interrupted() {

}
