// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "ReverseFeed.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

ReverseFeed::ReverseFeed(double Duration): Command() {
    m_Duration = Duration;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::feedRoller.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void ReverseFeed::Initialize() {
    SetTimeout(0.5);
    Robot::feedRoller->RunOut();
}

// Called repeatedly when this Command is scheduled to run
void ReverseFeed::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ReverseFeed::IsFinished() {
    return IsTimedOut();
}

// Called once after isFinished returns true
void ReverseFeed::End() {
	Robot::feedRoller->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ReverseFeed::Interrupted() {
    End();
}
