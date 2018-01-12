#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "ctre/Phoenix.h"

std::shared_ptr<WPI_TalonSRX> RobotMap::subDriveBaseSRXleft;
std::shared_ptr<WPI_TalonSRX> RobotMap::subDriveBaseSRXright;
std::shared_ptr<frc::DifferentialDrive> RobotMap::subDriveBaseMyFirstDifferentialDrive;

std::shared_ptr<WPI_TalonSRX> RobotMap::subDriveBaseSRXleftSlave;
std::shared_ptr<WPI_TalonSRX> RobotMap::subDriveBaseSRXrightSlave;

std::shared_ptr<WPI_TalonSRX> RobotMap::subIntakeTnxRight;
std::shared_ptr<WPI_TalonSRX> RobotMap::subIntakeTnxLeft;

void RobotMap::init() {

	//DriveBase Actuators
    subDriveBaseSRXleft.reset(new WPI_TalonSRX(1));
    subDriveBaseSRXright.reset(new WPI_TalonSRX(3));
    subDriveBaseMyFirstDifferentialDrive.reset(new frc::DifferentialDrive(*subDriveBaseSRXleft, *subDriveBaseSRXright));
    subDriveBaseMyFirstDifferentialDrive->SetSafetyEnabled(false);
	subDriveBaseMyFirstDifferentialDrive->SetExpiration(0.1);
	subDriveBaseMyFirstDifferentialDrive->SetMaxOutput(1.0);
	subDriveBaseSRXleftSlave.reset(new WPI_TalonSRX(2));
	subDriveBaseSRXleftSlave->Set( ctre::phoenix::motorcontrol::ControlMode::Follower, 1);
	subDriveBaseSRXrightSlave.reset(new WPI_TalonSRX(4));
	subDriveBaseSRXrightSlave->Set( ctre::phoenix::motorcontrol::ControlMode::Follower, 3);

	//Intake Actuators
    subIntakeTnxLeft.reset(new WPI_TalonSRX(5));
    subIntakeTnxRight.reset(new WPI_TalonSRX(6));
}
