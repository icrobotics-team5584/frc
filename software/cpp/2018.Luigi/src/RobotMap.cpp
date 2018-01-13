#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "ctre/Phoenix.h"

//Define DriveBase Actuators
std::shared_ptr<WPI_TalonSRX> RobotMap::subDriveBaseSRXleft;
std::shared_ptr<WPI_TalonSRX> RobotMap::subDriveBaseSRXright;
std::shared_ptr<frc::DifferentialDrive> RobotMap::subDriveBaseDifferentialDrive;
std::shared_ptr<WPI_TalonSRX> RobotMap::subDriveBaseSRXleftSlave;
std::shared_ptr<WPI_TalonSRX> RobotMap::subDriveBaseSRXrightSlave;

//Define Intake Actuators
std::shared_ptr<WPI_TalonSRX> RobotMap::subIntakeTnxRight;
std::shared_ptr<WPI_TalonSRX> RobotMap::subIntakeTnxLeft;
std::shared_ptr<WPI_TalonSRX> RobotMap::subIntakeTnxBottom;
std::shared_ptr<WPI_TalonSRX> RobotMap::subArmLiftLeft;
std::shared_ptr<WPI_TalonSRX> RobotMap::subArmLiftRight;


void RobotMap::init() {

	//Initiate DriveBase Actuators
    subDriveBaseSRXleft.reset(new WPI_TalonSRX(1));
    subDriveBaseSRXright.reset(new WPI_TalonSRX(3));
    subDriveBaseDifferentialDrive.reset(new frc::DifferentialDrive(*subDriveBaseSRXleft, *subDriveBaseSRXright));
    subDriveBaseDifferentialDrive->SetSafetyEnabled(false);
    subDriveBaseDifferentialDrive->SetExpiration(0.1);
    subDriveBaseDifferentialDrive->SetMaxOutput(1.0);
	subDriveBaseSRXleftSlave.reset(new WPI_TalonSRX(2));
	subDriveBaseSRXleftSlave->Set( ctre::phoenix::motorcontrol::ControlMode::Follower, 1);
	subDriveBaseSRXrightSlave.reset(new WPI_TalonSRX(4));
	subDriveBaseSRXrightSlave->Set( ctre::phoenix::motorcontrol::ControlMode::Follower, 3);

	//Intake Actuators
    subIntakeTnxLeft.reset(new WPI_TalonSRX(7));
    subIntakeTnxRight.reset(new WPI_TalonSRX(8));
    subIntakeTnxBottom.reset(new WPI_TalonSRX(7));
    subArmLiftLeft.reset(new WPI_TalonSRX(6));
    subArmLiftLeft.reset(new WPI_TalonSRX(5));
}
