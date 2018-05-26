#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "ctre/Phoenix.h"
#include "WPILib.h"

std::shared_ptr<WPI_TalonSRX> RobotMap::subDriveBaseTnxFrontRight;
std::shared_ptr<WPI_TalonSRX> RobotMap::subDriveBaseTnxFrontLeft;
std::shared_ptr<frc::DifferentialDrive> RobotMap::subDriveBaseDifDrive;
std::shared_ptr<WPI_TalonSRX> RobotMap::subDriveBaseTnxBackLeft;
std::shared_ptr<WPI_TalonSRX> RobotMap::subDriveBaseTnxBackRight;

void RobotMap::init() {

	//Create drive motors
    subDriveBaseTnxFrontRight.reset(new WPI_TalonSRX(7));
    subDriveBaseTnxFrontLeft.reset(new WPI_TalonSRX(8));
    subDriveBaseTnxBackLeft.reset(new WPI_TalonSRX(6));
    subDriveBaseTnxBackRight.reset(new WPI_TalonSRX(5));
    
    //Define slaves
    subDriveBaseTnxFrontRight->Set(ControlMode::Follower, 5);	//Follow backRight
    subDriveBaseTnxFrontLeft->Set(ControlMode::Follower, 6);	//Follow backLeft
    
    //Setup differential drive
    subDriveBaseDifDrive.reset(new DifferentialDrive(*subDriveBaseTnxFrontLeft, *subDriveBaseTnxFrontRight));
    subDriveBaseDifDrive->SetSafetyEnabled(true);
    subDriveBaseDifDrive->SetExpiration(0.1);
    subDriveBaseDifDrive->SetMaxOutput(1.0);

}
