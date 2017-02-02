// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "RunShooterMotors.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

RunShooterMotors::RunShooterMotors(double duration): Command() {
    m_duration = duration;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::shooterFlywheels.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void RunShooterMotors::Initialize() {
	SetTimeout(5);
    Robot::shooterFlywheels->Run();
}

// Called repeatedly when this Command is scheduled to run
void RunShooterMotors::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool RunShooterMotors::IsFinished() {
    return IsTimedOut();
}

// Called once after isFinished returns true
void RunShooterMotors::End() {
    Robot::shooterFlywheels->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunShooterMotors::Interrupted() {
    End();
}