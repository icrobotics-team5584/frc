#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "ctre/Phoenix.h"
#include "WPILib.h"

std::shared_ptr<WPI_TalonSRX> RobotMap::subDriveBaseTnxFrontRight;
std::shared_ptr<WPI_TalonSRX> RobotMap::subDriveBaseTnxFrontLeft;
std::shared_ptr<frc::DifferentialDrive> RobotMap::subDriveBaseDifDrive;
std::shared_ptr<WPI_TalonSRX> RobotMap::subDriveBaseTnxBackLeft;
std::shared_ptr<WPI_TalonSRX> RobotMap::subDriveBaseTnxBackRight;

std::shared_ptr<WPI_TalonSRX> RobotMap::subIntakeTnxLeft;
std::shared_ptr<WPI_TalonSRX> RobotMap::subIntakeTnxRight;

std::shared_ptr<WPI_TalonSRX> RobotMap::subEncodedArmTnx;
std::shared_ptr<AnalogInput> RobotMap::subEncodedArmPot;


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
    subDriveBaseDifDrive.reset(new DifferentialDrive(*subDriveBaseTnxBackLeft, *subDriveBaseTnxBackRight));
    subDriveBaseDifDrive->SetSafetyEnabled(true);
    subDriveBaseDifDrive->SetExpiration(0.1);
    subDriveBaseDifDrive->SetMaxOutput(1.0);

    //setup Intake motors
    subIntakeTnxRight.reset(new WPI_TalonSRX(2));
    subIntakeTnxLeft.reset(new WPI_TalonSRX(1));

    //setup EncodedArm Actuator/Sensors
    subEncodedArmTnx.reset(new WPI_TalonSRX(4));
    subEncodedArmPot.reset(new AnalogInput(0));
}
