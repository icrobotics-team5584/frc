#include "Robot.h"
#include "Commands/CmdAutoMotionProfileTest.h"

//Forward Define Subsystems
std::shared_ptr<SubDriveBase> Robot::subDriveBase;
std::shared_ptr<SubIntake> Robot::subIntake;
std::shared_ptr<SubArmLift> Robot::subArmLift;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<SubEncodedArmLift> Robot::subEncodedArmLift;


void Robot::RobotInit() {
	RobotMap::init();

	//Initiate Subsystems
	subDriveBase.reset(new SubDriveBase());
	subIntake.reset(new SubIntake());
	subArmLift.reset(new SubArmLift());
	subEncodedArmLift.reset(new SubEncodedArmLift());
	oi.reset(new OI());

	//Setup Auto Position Chooser
	std::cout << "setup auto chooser \n";
	positionChooser.AddDefault("Left Starting Position", new CmdAutoMotionProfileTest());
	positionChooser.AddObject("Middle Starting Position", new CmdAutoMotionProfileTest());
	positionChooser.AddObject("Right Starting Position", new CmdAutoMotionProfileTest());
	frc::SmartDashboard::PutData("Auto Modes", &positionChooser);

	//Setup Auto Task Chooser
	taskChooser.AddDefault("Go for Switch", Switch);
	taskChooser.AddObject("Get that Scale", Scale);
	taskChooser.AddObject("ACHIEVE EVERYTHING!", Both);
	taskChooser.AddObject("Don't. Move.", Nothing);
}

void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();

	autonomousCommand = positionChooser.GetSelected();
	if (autonomousCommand != nullptr)
		autonomousCommand->Start();



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
