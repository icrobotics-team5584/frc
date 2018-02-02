#include "Robot.h"

//Define Subsystems
std::shared_ptr<SubDriveBase> Robot::subDriveBase;
std::shared_ptr<SubIntake> Robot::subIntake;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<SubEncodedArmLift> Robot::subEncodedArmLift;
std::shared_ptr<SubCameras> Robot::subCameras;

std::shared_ptr<MotionProfileData> Robot::MPData;

void Robot::RobotInit() {
	RobotMap::init();

	MPData.reset(new MotionProfileData());

	//Initiate Subsystems
	subDriveBase.reset(new SubDriveBase());
	subIntake.reset(new SubIntake());
	subEncodedArmLift.reset(new SubEncodedArmLift());
//	subCameras.reset(new SubCameras);
	oi.reset(new OI());

	//Setup Auto Chooser
	autoSelector.SendOptionsToDashboard();
}

void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	//Remove any pre-existing MP Trajectory Points in Talons
	RobotMap::subDriveBaseSRXright->ClearMotionProfileTrajectories();
	RobotMap::subDriveBaseSRXleft->ClearMotionProfileTrajectories();

	//Reset Sensor positions to zero for future profiles
	RobotMap::subDriveBaseSRXright->SetSelectedSensorPosition(0, 0, 10);
	RobotMap::subDriveBaseSRXleft->SetSelectedSensorPosition(0, 0, 10);

	//Determine auto command selected from Dashboard and run
	autoSelector.SelectAndRun(autoSelector.GetStartingPosition(), autoSelector.GetAutonomousTask, gameData);
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
