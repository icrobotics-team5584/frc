// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "CmdAutoDriveToPeg.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

CmdAutoDriveToPeg::CmdAutoDriveToPeg(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::subDriveBase.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void CmdAutoDriveToPeg::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdAutoDriveToPeg::Execute() {
    double direction = Robot::subDriveBase->GetPegX();
    double power = 0.25;
    // we are driving backwards so ...
    power *= -1;
    direction *= -1;
	Robot::subDriveBase->Drive(power, direction);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdAutoDriveToPeg::IsFinished() {
    double range = Robot::subDriveBase->GetPegRange();
    if ( ( range == 0 ) && ( prevrange == 0 ) && ( prevprevrange == 0 ) )
        return true;
    if ( ( range < 200 ) && ( range != 0 ) )
        return true;
    prevprevrange = prevrange;
    prevrange = range;
    return false;
}

// Called once after isFinished returns true
void CmdAutoDriveToPeg::End() {
    Robot::subDriveBase->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdAutoDriveToPeg::Interrupted() {
    End();
}