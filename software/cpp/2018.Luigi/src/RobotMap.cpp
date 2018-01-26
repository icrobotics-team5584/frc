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
//std::shared_ptr<frc::AnalogInput> RobotMap::subDriveBaseUltrasonicInputFront;
//std::shared_ptr<frc::AnalogInput> RobotMap::subDriveBaseUltrasonicInputRight;
//std::shared_ptr<frc::AnalogInput> RobotMap::subDriveBaseUltrasonicInputBack;
//std::shared_ptr<frc::AnalogInput> RobotMap::subDriveBaseUltrasonicInputLeft;

std::shared_ptr<frc::Ultrasonic> RobotMap::subDriveBaseUltrasonicInputFront;
std::shared_ptr<frc::Ultrasonic> RobotMap::subDriveBaseUltrasonicInputRight;
std::shared_ptr<frc::Ultrasonic> RobotMap::subDriveBaseUltrasonicInputBack;
std::shared_ptr<frc::Ultrasonic> RobotMap::subDriveBaseUltrasonicInputLeft;

//Define arm lift Actuators / Actuator
std::shared_ptr<WPI_TalonSRX> RobotMap::subEncodedArmLiftSrxMaster;


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
		// Setup encoders on master drive motors for position control:
	subDriveBaseSRXleft->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
	subDriveBaseSRXright->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
	subDriveBaseSRXleft->ConfigNeutralDeadband(0.001, 10);
	subDriveBaseSRXright->ConfigNeutralDeadband(0.001, 10);
	subDriveBaseSRXleft->ConfigMotionProfileTrajectoryPeriod(0, 10);
	subDriveBaseSRXright->ConfigMotionProfileTrajectoryPeriod(0, 10);
	subDriveBaseSRXleft->SetSensorPhase(true);
	subDriveBaseSRXright->SetSensorPhase(true);
		// Setup FPID parameters for master drive motors:
	double LeftFgain = 0.181434;    double RightFgain = 0.180678;
	double LeftPgain = 2.0;      double RightPgain = 2.0;
	double LeftIgain = 0.0;      double RightIgain = 0.0;
	double LeftDgain = 20.0;     double RightDgain = 20.0;
	subDriveBaseSRXleft->SelectProfileSlot(0, 0);
	subDriveBaseSRXleft->Config_kF(0, LeftFgain, 10);
	subDriveBaseSRXleft->Config_kP(0, LeftPgain, 10);
	subDriveBaseSRXleft->Config_kI(0, LeftIgain, 10);
	subDriveBaseSRXleft->Config_kD(0, LeftDgain, 10);
	subDriveBaseSRXright->SelectProfileSlot(0, 0);
	subDriveBaseSRXright->Config_kF(0, RightFgain, 10);
	subDriveBaseSRXright->Config_kP(0, RightPgain, 10);
	subDriveBaseSRXright->Config_kI(0, RightIgain, 10);
	subDriveBaseSRXright->Config_kD(0, RightDgain, 10);

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

//    //Initiate Ultrasonic sensors
//    subDriveBaseUltrasonicInputFront.reset(new frc::AnalogInput(0));
//    	//lw->AddSensor("SubUltrasonic", "UltrasonicInputFront",  subDriveBaseUltrasonicInputFront);
//    subDriveBaseUltrasonicInputRight.reset(new frc::AnalogInput(1));
//    	//lw->AddSensor("SubUltrasonic", "UltrasonicInputFront",  subDriveBaseUltrasonicInputRight);
//    subDriveBaseUltrasonicInputBack.reset(new frc::AnalogInput(2));
//    	//lw->AddSensor("SubUltrasonic", "UltrasonicInputFront",  subDriveBaseUltrasonicInputBack);
//    subDriveBaseUltrasonicInputLeft.reset(new frc::AnalogInput(3));
//    	//lw->AddSensor("SubUltrasonic", "UltrasonicInputFront",  subDriveBaseUltrasonicInputLeft);

    //initiate echo Ultrasonic objects
    subDriveBaseUltrasonicInputFront.reset(new frc::Ultrasonic(0,1));
    subDriveBaseUltrasonicInputRight.reset(new frc::Ultrasonic(2,3));
    subDriveBaseUltrasonicInputBack.reset(new frc::Ultrasonic(4,5));
    subDriveBaseUltrasonicInputLeft.reset(new frc::Ultrasonic(6,7));


    //Initiate arm lift Actuators / Actuator
    subEncodedArmLiftSrxMaster.reset(new WPI_TalonSRX(5));

}
