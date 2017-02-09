// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Robot.h"
#include <CameraServer.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<SubDriveBase> Robot::subDriveBase;
std::shared_ptr<SubGearCatcher> Robot::subGearCatcher;
std::shared_ptr<SubClimber> Robot::subClimber;
std::shared_ptr<SubShooter> Robot::subShooter;
std::shared_ptr<SubIntake> Robot::subIntake;
std::shared_ptr<SubFeeder> Robot::subFeeder;
std::unique_ptr<OI> Robot::oi;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

void Robot::RobotInit() {

    RobotMap::init();

    // Setup camera ...
    // CameraServer::GetInstance()->StartAutomaticCapture();
    cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
    // NOTE: 640x480 => observed as 4mbps at 7/8fps in smart dashboard
    // NOTE: 320x240 => observed as 3mbps at 15/16fps in smart dashboard
    camera.SetResolution(320, 240);

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    subDriveBase.reset(new SubDriveBase());
    subGearCatcher.reset(new SubGearCatcher());
    subClimber.reset(new SubClimber());
    subShooter.reset(new SubShooter());
    subIntake.reset(new SubIntake());
    subFeeder.reset(new SubFeeder());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS

    // This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());

	// instantiate the command used for the autonomous period
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	autonomousCommand.reset(new CmdAutonomous());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
  }

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {
	lw->Run();
}

START_ROBOT_CLASS(Robot);

