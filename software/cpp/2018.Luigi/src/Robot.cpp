#include "Robot.h"

//Define Subsystems
std::shared_ptr<SubDriveBase> Robot::subDriveBase;
std::shared_ptr<SubIntake> Robot::subIntake;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<SubEncodedArmLift> Robot::subEncodedArmLift;
std::shared_ptr<SubCameras> Robot::subCameras;

std::shared_ptr<MotionProfileData> Robot::MPData;

void Robot::RobotInit() {
	std::cout << "Running Robot::RobotInit()" << std::endl;

	RobotMap::init();
	MPData.reset(new MotionProfileData());

	//Initiate Subsystems
	subDriveBase.reset(new SubDriveBase());
	subIntake.reset(new SubIntake());
	subEncodedArmLift.reset(new SubEncodedArmLift());
//	subCameras.reset(new SubCameras);
	oi.reset(new OI());


	//Setup Auto Chooser
	std::cout << "creating and sending autoChooser" << std::endl;
	autoChooser.AddDefault("Choose for me", new CmdAutonomous());
	frc::SmartDashboard::PutData("Autonomous", &autoChooser);
}

void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	std::cout << "Running Robot::AutonomousInit()" << std::endl;
	autonomousCommand = autoChooser.GetSelected();

	if (autonomousCommand != nullptr)
		std::cout << "About to run autonomousCommand->Start()" << std::endl;
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
