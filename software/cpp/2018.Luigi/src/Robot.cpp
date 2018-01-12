#include "Robot.h"

//Forward Define Subsystems
std::shared_ptr<SubDriveBase> Robot::subDriveBase;
std::shared_ptr<SubIntake> Robot::subIntake;
std::unique_ptr<OI> Robot::oi;


void Robot::RobotInit() {
	RobotMap::init();

	//Initiate Subsystems
	subDriveBase.reset(new SubDriveBase());
	subIntake.reset(new SubIntake());
	oi.reset(new OI());

	//Setup Auto Chooser
	chooser.AddDefault("Forward", new CmdAutoForward());
	chooser.AddObject("Backward", new CmdAutoBackward());
	frc::SmartDashboard::PutData("Auto Modes", &chooser);
}

void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	autonomousCommand = chooser.GetSelected();
	if (autonomousCommand != nullptr)
		autonomousCommand->Start();

	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();

	//Probably want to drag in each value, make a string or array for use in switch/case statment!!  gameData is pionter to string array!!
}

void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	if (autonomousCommand != nullptr)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

START_ROBOT_CLASS(Robot);
