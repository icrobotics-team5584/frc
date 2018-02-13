#include "Robot.h"

//Define Subsystems
std::shared_ptr<SubDriveBase> Robot::subDriveBase;
std::shared_ptr<SubIntake> Robot::subIntake;
std::shared_ptr<SubEncodedArmLift> Robot::subEncodedArmLift;
std::shared_ptr<SubCameras> Robot::subCameras;
std::shared_ptr<SubRamp> Robot::subRamp;

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
	subCameras.reset(new SubCameras);
	subRamp.reset(new SubRamp);

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

	//Reset sensors to zero
	subDriveBase->ClearMPBuffers();
	subDriveBase->ZeroDriveEncoders();
	subEncodedArmLift->Reset();

	//Determine auto command selected from Dashboard and run
	autoSelector.SelectAndRun(autoSelector.GetStartingPosition(), autoSelector.GetAutonomousTask(), gameData);

	//Use this for a predetermined autonomous routine
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
