#include "Robot.h"
#include "Commands/CmdAutoMotionProfileTest.h"

//Forward Define Subsystems
std::shared_ptr<SubDriveBase> Robot::subDriveBase;
std::shared_ptr<SubIntake> Robot::subIntake;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<SubEncodedArmLift> Robot::subEncodedArmLift;
std::shared_ptr<SubCameras> Robot::subCameras;

void Robot::RobotInit() {
	RobotMap::init();

	//Initiate Subsystems
	subDriveBase.reset(new SubDriveBase());
	subIntake.reset(new SubIntake());
	subEncodedArmLift.reset(new SubEncodedArmLift());
	subCameras.reset(new SubCameras);
	oi.reset(new OI());


	//Setup Auto Position Chooser

	std::cout << "setup auto chooser \n";
	positionChooser.AddDefault("Left Starting Position", new CmdAutoMotionProfileTest());
	positionChooser.AddObject("Middle Starting Position", new CmdAutoMotionProfileTest());
	positionChooser.AddObject("Right Starting Position", new CmdAutoMotionProfileTest());
	frc::SmartDashboard::PutData("Starting Position", &positionChooser);

	//Setup Auto Task Chooser - Removed and replaced with a number selection on dash
//	taskChooser.AddDefault("Go for Switch", Switch);
//	taskChooser.AddObject("Get that Scale", Scale);
//	taskChooser.AddObject("ACHIEVE EVERYTHING!", Both);
//	taskChooser.AddObject("Don't. Move.", Nothing);
//	frc::SmartDashboard::PutData("Autonomous Tasks", &taskChooser);

	SmartDashboard::PutNumber("intAutonomousTask", intAutonomousTask);
}

void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
//	intAutonomousTask = SmartDashboard::GetNumber("intAutonomousTask", 0);
//	autonomousTask.reset(new task);
//	switch(intAutonomousTask){
//	case 0:
//		*autonomousTask = Nothing;
//		break;
//	case 1:
//		*autonomousTask = Scale;
//		break;
//	case 2:
//		*autonomousTask = Switch;
//		break;
//	case 3:
//		*autonomousTask = Both;
//		break;
//	}
	autonomousCommand = positionChooser.GetSelected();

	if (autonomousCommand != nullptr)
		autonomousCommand->Start();
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
