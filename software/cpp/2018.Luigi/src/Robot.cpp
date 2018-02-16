#include "Robot.h"

//Define Subsystems
std::shared_ptr<SubDriveBase> Robot::subDriveBase;
std::shared_ptr<SubIntake> Robot::subIntake;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<SubEncodedArmLift> Robot::subEncodedArmLift;
std::shared_ptr<SubCameras> Robot::subCameras;
std::shared_ptr<SubRamp> Robot::subRamp;

std::shared_ptr<MotionProfileData> Robot::MPData;
GameData Robot::gameData;
AutonomousSelector Robot::autoSelector;

Robot* Robot::instance = 0;
Robot* Robot::getInstance(){
	if (instance == 0) {
		instance = new Robot();
	}
	return instance;
}

Robot::Robot() : frc::TimedRobot() {

}

void Robot::RobotInit() {
	RobotMap::init();

	MPData.reset(new MotionProfileData());

	//Initiate Subsystems
	subDriveBase.reset(new SubDriveBase());
	subIntake.reset(new SubIntake());
	subEncodedArmLift.reset(new SubEncodedArmLift());
	subCameras.reset(new SubCameras);
	subRamp.reset(new SubRamp);
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

int main() {
    if (!HAL_Initialize(500, 0)) {
      llvm::errs() << "FATAL ERROR: HAL could not be initialized\n";
      return -1;
    }
    HAL_Report(HALUsageReporting::kResourceType_Language,
               HALUsageReporting::kLanguage_CPlusPlus);
    llvm::outs() << "\n********** Robot program starting **********\n";
    Robot::getInstance()->StartCompetition();
  }

//START_ROBOT_CLASS(Robot);
