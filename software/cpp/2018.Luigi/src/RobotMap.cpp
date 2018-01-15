#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "ctre/Phoenix.h"
#include "WPILib.h"

//Define DriveBase Actuators
std::shared_ptr<WPI_TalonSRX> RobotMap::subDriveBaseSRXleft;
std::shared_ptr<WPI_TalonSRX> RobotMap::subDriveBaseSRXright;
std::shared_ptr<frc::DifferentialDrive> RobotMap::subDriveBaseDifferentialDrive;
std::shared_ptr<WPI_TalonSRX> RobotMap::subDriveBaseSRXleftSlave;
std::shared_ptr<WPI_TalonSRX> RobotMap::subDriveBaseSRXrightSlave;

//Define Intake Actuators and Sensors
std::shared_ptr<WPI_TalonSRX> RobotMap::subIntakeTnxRight;
std::shared_ptr<WPI_TalonSRX> RobotMap::subIntakeTnxLeft;
std::shared_ptr<WPI_TalonSRX> RobotMap::subIntakeTnxBottom;
std::shared_ptr<DigitalInput> RobotMap::subIntakeSwtRightLimit;
std::shared_ptr<DigitalInput> RobotMap::subIntakeSwtLeftLimit;

//Define Lift Actuators
std::shared_ptr<WPI_TalonSRX> RobotMap::subArmLiftLeft;
std::shared_ptr<WPI_TalonSRX> RobotMap::subArmLiftRight;
std::shared_ptr<DigitalInput> RobotMap::subArmLiftTopLimit;
std::shared_ptr<DigitalInput> RobotMap::subArmLiftBottomLimit;

//Define Ultrasonic sensors
std::shared_ptr<frc::AnalogInput> RobotMap::subDriveBaseUltrasonicInputFront;
std::shared_ptr<frc::AnalogInput> RobotMap::subDriveBaseUltrasonicInputRight;
std::shared_ptr<frc::AnalogInput> RobotMap::subDriveBaseUltrasonicInputBack;
std::shared_ptr<frc::AnalogInput> RobotMap::subDriveBaseUltrasonicInputLeft;



void RobotMap::init() {

	//Initiate DriveBase Actuators
		//Masters:
    subDriveBaseSRXleft.reset(new WPI_TalonSRX(1));
    subDriveBaseSRXright.reset(new WPI_TalonSRX(3));
		//Slaves:
    subDriveBaseSRXleftSlave.reset(new WPI_TalonSRX(2));
    subDriveBaseSRXleftSlave->Set( ctre::phoenix::motorcontrol::ControlMode::Follower, 1);
	subDriveBaseSRXrightSlave.reset(new WPI_TalonSRX(4));
	subDriveBaseSRXrightSlave->Set( ctre::phoenix::motorcontrol::ControlMode::Follower, 3);
		//Differential Drive:
	subDriveBaseDifferentialDrive.reset(new frc::DifferentialDrive(*subDriveBaseSRXleft, *subDriveBaseSRXright));
	subDriveBaseDifferentialDrive->SetSafetyEnabled(false);
	subDriveBaseDifferentialDrive->SetExpiration(0.1);
	subDriveBaseDifferentialDrive->SetMaxOutput(1.0);

	//Initiate Intake Actuators
    subIntakeTnxLeft.reset(new WPI_TalonSRX(7));
    subIntakeTnxRight.reset(new WPI_TalonSRX(8));
    //Initiate Intake Sensors
    subIntakeTnxBottom.reset(new WPI_TalonSRX(9));
    subIntakeSwtLeftLimit.reset(new DigitalInput(0));
    subIntakeSwtRightLimit.reset(new DigitalInput(1));

    //Initiate Lift Actuators
    subArmLiftLeft.reset(new WPI_TalonSRX(6));
    subArmLiftRight.reset(new WPI_TalonSRX(5));
    //Initiate Lift Sensors
    subArmLiftTopLimit.reset(new DigitalInput(3));
    subArmLiftTopLimit.reset(new DigitalInput(4));


    //Initiate Ultrasonic sensors
    subDriveBaseUltrasonicInputFront.reset(new frc::AnalogInput(0));
    	//lw->AddSensor("SubUltrasonic", "UltrasonicInputFront",  subDriveBaseUltrasonicInputFront);
    subDriveBaseUltrasonicInputRight.reset(new frc::AnalogInput(1));
    	//lw->AddSensor("SubUltrasonic", "UltrasonicInputFront",  subDriveBaseUltrasonicInputRight);
    subDriveBaseUltrasonicInputBack.reset(new frc::AnalogInput(2));
    	//lw->AddSensor("SubUltrasonic", "UltrasonicInputFront",  subDriveBaseUltrasonicInputBack);
    subDriveBaseUltrasonicInputLeft.reset(new frc::AnalogInput(3));
    	//lw->AddSensor("SubUltrasonic", "UltrasonicInputFront",  subDriveBaseUltrasonicInputLeft);
}
