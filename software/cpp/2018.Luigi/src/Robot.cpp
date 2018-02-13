#include "Robot.h"

//Define Subsystems
std::shared_ptr<SubDriveBase> Robot::subDriveBase;
std::shared_ptr<SubIntake> Robot::subIntake;
std::shared_ptr<SubEncodedArmLift> Robot::subEncodedArmLift;
std::shared_ptr<SubCameras> Robot::subCameras;

//Define Operator interface
std::unique_ptr<OI> Robot::oi;

//Define Autonomous Objects
std::shared_ptr<MotionProfileData> Robot::MPData;
GameData Robot::gameData;
AutonomousSelector Robot::autoSelector;

void Robot::RobotInit() {
	RobotMap::init();

	//Initiate Subsystems
	subDriveBase.reset(new SubDriveBase());
	subIntake.reset(new SubIntake());
	subEncodedArmLift.reset(new SubEncodedArmLift());
//	subCameras.reset(new SubCameras);

	//Initiate Operator Interface
	oi.reset(new OI());

	//Setup Auto Chooser
	autoSelector.SendOptionsToDashboard();
	MPData.reset(new MotionProfileData());
}

void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	gameData.UpdateGameData();

	//Remove any pre-existing MP Trajectory Points in Talons
	RobotMap::subDriveBaseSRXright->ClearMotionProfileTrajectories();
	RobotMap::subDriveBaseSRXleft->ClearMotionProfileTrajectories();

	//Reset Sensor positions to zero for future profiles
	RobotMap::subDriveBaseSRXright->SetSelectedSensorPosition(0, 0, 10);
	RobotMap::subDriveBaseSRXleft->SetSelectedSensorPosition(0, 0, 10);

	//Make sure lift starts at zero
	subEncodedArmLift->Reset();

	//Determine auto command selected from Dashboard and run
	autoSelector.SelectAndRun(autoSelector.GetStartingPosition(), autoSelector.GetAutonomousTask(), gameData);
//	static CmdAutonomous ac;
//	ac.Start();
}

void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	autoSelector.StopAutoCommand();
}

void Robot::TeleopPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

START_ROBOT_CLASS(Robot);
